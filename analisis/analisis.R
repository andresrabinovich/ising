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
datos <-data.frame(read_csv("corridas/energias.txt", col_names = FALSE))
n = 256
ggplot(data=datos, aes(x=1:nrow(datos), y=X1/(n*n))) + 
  geom_point() + 
  labs(title="Ising J=0, B=-1") +
  labs(x="Paso", y="Energia") +
  theme_original()
configuracion <- data.frame(read_csv("corridas/configuracion.txt", col_names = FALSE))
for(i in 1:100){
  heatmap(as.matrix(configuracion)[(((i-1)*n)+1):(i*n), ], Colv=NA, Rowv=NA, scale='none', labRow = NA, labCol = NA)
  invisible(readline(prompt="Press [enter] to continue"))
}
