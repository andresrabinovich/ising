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


#ej1a
datos <-data.frame(read_csv("corridas/energia.txt"))
#datos
dim(datos)
ggplot(data=datos, aes(x=1:nrow(datos), y=energia)) + 
  geom_point() + 
  #labs(title="Ising J=0, B=-1") +
  labs(x=colnames(datos)[1], y=colnames(datos)[2]) +
  theme_original()
datos <-data.frame(read_csv("corridas/magnetizacion.txt"))
datos
dim(datos)
ggplot(data=datos, aes(x=1:nrow(datos), y=magnetizacion)) + 
  geom_point() + 
  #labs(title="Ising J=0, B=-1") +
  labs(x=colnames(datos)[1], y=colnames(datos)[2]) +
  theme_original()
configuracion <- data.frame(read_csv("corridas/configuraciones.txt", col_names = FALSE))
dim(configuracion)
for(i in seq(from=1, to=(nrow(configuracion)/ncol(configuracion)), by=1)){
  heatmap(as.matrix(configuracion)[(((i-1)*ncol(configuracion))+1):(i*ncol(configuracion)), ], Colv=NA, Rowv=NA, scale='none', labRow = NA, labCol = NA)
  invisible(readline(prompt="Press [enter] to continue"))
}
