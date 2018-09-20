weight =0000
sheep = 0.000122851    #sheep/m2 
output.weight <- c()
output.npp_graze <- c()
output.n_total <- c()
for (i in 1:365) {
  npp_graze = sheep * weight * 0.04 *0.95 *0.475
  weight = 0.985 * weight + 0.65 * npp_graze/0.475/sheep
  if(weight > 100000){
    weight =100000
  }
  n_total = n_total + npp_graze
  output.weight <- c(output.weight, weight)
  output.npp_graze <- c(output.npp_graze, npp_graze)
  output.n_total <- c(output.n_total,n_total)
  
}