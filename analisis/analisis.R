#Cargamos las librerías que vamos a usar y generamos el theme para los plots
library(ggplot2)
library(readr)
theme_original <- function (base_size = 10, base_family = "") {
  theme_gray(base_size = base_size, base_family = base_family) %+replace% 
    theme(
      plot.title = element_text(hjust = 0.5),
      panel.background = element_rect(fill="#e1e1e1"),
      panel.grid.minor = element_line(size=0.1, color="white"),
      panel.grid.major = element_line(size=0.2, color="white"),
      text = element_text(family = base_family, face = "plain",
                          color = "black", size = base_size,
                          hjust = 0.5, vjust = 0.5, angle = 0, lineheight = 0.9,
                          margin = margin(), debug = FALSE)
    )
}
setwd("~/fisica_computacional/ising/")


#TERMALIZACION
datos <-data.frame(read_csv("corridas/termalizacion/magnetizacion.txt"))
teorico <- tanh(1/unique(datos$T))
datos$T <- as.factor(datos$T)
ggplot(data=datos, aes(x=iteracion, y=magnetizacion, colour=T)) + 
  geom_point() + 
  geom_hline(yintercept = teorico[1]) + 
  geom_hline(yintercept = teorico[2]) + 
  geom_hline(yintercept = teorico[3]) + 
  geom_hline(yintercept = teorico[4]) + 
  geom_hline(yintercept = teorico[5]) + 
  geom_hline(yintercept = teorico[6]) + 
  geom_hline(yintercept = teorico[7]) + 
  geom_hline(yintercept = teorico[8]) + 
  labs(title="Magnetización J=0, B=1") +
  labs(x=colnames(datos)[1], y=colnames(datos)[3]) +
  theme_original()

#AUTOCORRELACION
datos   <-data.frame(read_csv("corridas/autocorrelacion_magnetizacion.txt"))
autocorrelacion <- matrix(ncol=2, nrow=0)
lag.max = 10000
for(i in unique(datos$T)){
  energia_t <- datos$magnetizacion[datos$T == i]
  a<-acf(energia_t, lag.max = lag.max)
  autocorrelacion <- rbind(autocorrelacion, cbind(a$acf, rep(i, (lag.max+1))))
}
autocorrelacion <- data.frame(autocorrelacion)
colnames(autocorrelacion) <- c("rho", "T")
autocorrelacion$T <- as.factor(autocorrelacion$T)

ggplot(data=autocorrelacion, aes(x=rep(1:(lag.max+1), times=length(unique(datos$T))), y=rho)) + 
  geom_line(aes(color=T)) + 
  labs(title="Autocorrelación magnetizacion (B=0)") +
  labs(x="k", y="rho") +
  theme_original()

#Autocorrelacion de forma casera
#s <- sd(energia_t)^2
#energia_t <- energia_t-mean(energia_t)
#comienzo = 1:length(datos$energia[datos$T == 1])
#ro <- c()
#for(k in 0:10000){
  #  comienzo <- 1:(length(energia_t)-k)
  #  r <- mean(energia_t[comienzo] * energia_t[comienzo+k])/mean(energia_t[comienzo]^2)
  #ro <- c(ro,r)
#}
#plot(ro)

#MAGNETIZACION ESPONTANEA SIN CORONA
datos   <-data.frame(read_csv("corridas/sin_corona/magnetizacion.txt"))
ggplot(data=datos, aes(x=magnetizacion)) + 
  geom_histogram(aes(y=..count../sum(..count..)), 
  breaks=seq(-1, 1, by = 0.01), 
  col="black", 
  fill="white") + 
  labs(title="Histogram for Age") +
  labs(x="Age", y="Count") +  
  labs(title="Magnetización (T entre 0.5 y 5), B=0") +
  labs(x="Magnetización", y="Densidad") +
  theme_original()


#MAGNETIZACION ESPONTANEA
datos   <-data.frame(read_csv("corridas/con_corona/magnetizacion.txt"))
magnetizacion_media <- aggregate(formula = magnetizacion ~ T+n, data = datos, FUN=mean)
magnetizacion_media$n <- as.factor(magnetizacion_media$n)
ggplot(data=magnetizacion_media, aes(x=T, y=magnetizacion)) + 
  geom_point(aes(color=n)) + 
  labs(title="Magnetización (B=0)") +
  labs(x="T", y="Magnetización media por particula") +
  theme_original()

#ENERGIA
datos   <-data.frame(read_csv("corridas/con_corona/energia.txt"))
energia_media <- aggregate(formula = energia ~ T+n, data = datos, FUN=mean)
energia_media$n <- as.factor(energia_media$n)
ggplot(data=energia_media, aes(x=T, y=energia)) + 
  geom_point(aes(color=n)) + 
  labs(title="Energía media (B=0)") +
  labs(x="T", y="Energía media por particula") +
  theme_original()

#SUSCEPTIBILIDAD MAGNETICA
datos   <-data.frame(read_csv("corridas/con_corona/magnetizacion.txt"))
susceptibilidad <- aggregate(formula = magnetizacion ~ T+n, data = datos, FUN=sd)
susceptibilidad$n <- as.factor(susceptibilidad$n)
ggplot(data=susceptibilidad, aes(x=T, y=magnetizacion)) + 
  geom_point(aes(color=n)) + 
  labs(title="Susceptibilidad (B=0)") +
  labs(x="T", y="Susceptibilidad por particula") +
  theme_original()

noisy.y <- susceptibilidad[susceptibilidad$n==32, c("T", "magnetizacion")]
model <- lm(noisy.y$magnetizacion ~ poly(noisy.y$T,20))
predicted.intervals <- predict(model,data.frame(x=noisy.y$T),interval='confidence', level=0.99)
plot(noisy.y)
lines(noisy.y$T,predicted.intervals[,1],col='green',lwd=3)
noisy.y$T[which.max(predicted.intervals[, 1])]

#Cv
datos   <-data.frame(read_csv("corridas/con_corona/energia.txt"))
cv      <- aggregate(formula = energia ~ T+n, data = datos, FUN=sd)
cv$n <- as.factor(cv$n)
ggplot(data=cv, aes(x=T, y=energia)) + 
  geom_point(aes(color=n)) + 
  labs(title="Cv (B=0)") +
  labs(x="T", y="Cv por particula") +
  theme_original()

noisy.y <- cv[cv$n==128, c("T", "energia")]
model <- lm(noisy.y$energia ~ poly(noisy.y$T,20))
predicted.intervals <- predict(model,data.frame(x=noisy.y$T),interval='confidence', level=0.99)
plot(noisy.y)
lines(noisy.y$T,predicted.intervals[,1],col='green',lwd=3)
noisy.y$T[which.max(predicted.intervals[, 1])]