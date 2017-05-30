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
setwd("~/Escritorio/fisica_computacional/ising/")


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

#MAGNETIZACION ESPONTANEA
datos   <-data.frame(read_csv("corridas/magnetizacion.txt"))
magnetizacion_media <- aggregate(formula = magnetizacion ~ T, data = datos, FUN=mean)
ggplot(data=magnetizacion_media, aes(x=T, y=magnetizacion)) + 
  geom_line() + 
  labs(title="Magnetización J=1, B=0") +
  labs(x=colnames(magnetizacion_media)[1], y=colnames(magnetizacion_media)[2]) +
  theme_original()

#ej1a
datos <-data.frame(read_csv("corridas/energia.txt"))
#datos
dim(datos)
ggplot(data=datos, aes(x=1:nrow(datos), y=energia)) + 
  geom_point() + 
  #labs(title="Ising J=0, B=-1") +
  labs(x=colnames(datos)[1], y=colnames(datos)[3]) +
  theme_original()

configuracion <- data.frame(read_csv("corridas/configuraciones.txt", col_names = FALSE))
dim(configuracion)
for(i in seq(from=1, to=(nrow(configuracion)/ncol(configuracion)), by=1)){
  heatmap(as.matrix(configuracion)[(((i-1)*ncol(configuracion))+1):(i*ncol(configuracion)), ], Colv=NA, Rowv=NA, scale='none', labRow = NA, labCol = NA)
  invisible(readline(prompt="Press [enter] to continue"))
}

