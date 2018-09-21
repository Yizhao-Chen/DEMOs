npp1 = 30;
npp2 = 50;

ft = 0.5;
fw = 0.6;    

#k_ml = 1/1.5
#k_sl = 1/3.86
#k_f  = 1/0.8
#k_s  = 1/5
#k_p  = 1/250

fml_f = 0.2;
fsl_f = 0.3;
fsl_s = 0.4;
ff_s = 0.35;
ff_p = 0.2;
fs_f = 0.15;
fs_p = 0.15;
fp_f = 0.5;

C_ml = 100;
C_sl = 100;
C_f = 50;
C_s = 500;
C_p = 1000;


a_matrix <- diag(-1,5,5)
a_matrix[3,1] <- 0.2
a_matrix[3,2] <- 0.3
a_matrix[4,2] <- 0.4
a_matrix[4,3] <- 0.35
a_matrix[5,3] <- 0.2
a_matrix[5,4] <- 0.15
a_matrix[3,4] <- 0.15
a_matrix[3,5] <- 0.5

kk_matrix <- diag(0,5,5)
kk_matrix[1,1] <- 0.67 * 0.5 * 0.6
kk_matrix[2,2] <- 0.26 * 0.5 * 0.6
kk_matrix[3,3] <- 1.25 * 0.5 * 0.6
kk_matrix[4,4] <- 0.2 * 0.5 * 0.6
kk_matrix[5,5] <- 0.004 * 0.5 * 0.6

c_matrix <- matrix(0,5,1)
c_next <- matrix(0,5,1)
alph <- matrix(0,5,5)
c_in <- matrix(0,5,1)
c_in[1,1] = 30
c_in[2,1] = 50

for (i in 1:100){
  c_matrix[1,1] = C_ml
  c_matrix[2,1] = C_sl
  c_matrix[3,1] = C_f
  c_matrix[4,1] = C_s
  c_matrix[5,1] = C_p
  alph <- a_matrix%*%kk_matrix
c_next <- c_in + c_matrix +alph %*%c_matrix
  C_ml = c_next[1,1]
  C_sl = c_next[2,1]
  C_f = c_next[3,1]
  C_s = c_next[4,1]
  C_p = c_next[5,1]
}
