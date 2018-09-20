#surface hydrological cycling 

#define essential variables & parameters
  Qmax = 50  #max water holding capacity
  k = 0.25#1.5#1.25#1.1#0.9#0.75#*0.5   #subsurface runoff rate
  k1 = 0.98
  Q <- c()   # water dynamic in the pool
  pd <- c()  #Precipitation dynamic
  P <- c()   #Precipitation input
  M <- c()
  sur_R <- c()
  sub_R <- c()
  sur_R = 0 #surface runoff initial value
  sub_R = 0 #subsurface runoff initial value
  Q = 10   #initial value of storage
  
  pd <- seq(from=1, to=200, by=1)            #increasing precipitation input case 2
  #pd <- rep(1:20,10)                          #periodic precipitation input case 3
for (x in 1:200){                             #time sequence simulation
  #pd[x] = 10                                 #non-change precipitation input case 1
  P[x] = pd[x]
  sub_R[x] = k * Q[x]                         #process 1:subsurface runoff
  M[x] = Q[x]+P[x]                            #total water input in moment x     
   if (M[x] >= Qmax){                         
     sur_R[x] = Q[x] + P[x] - Qmax - sub_R[x] #process 2:surface runoff
     if (sur_R[x]<0){
       sur_R[x]=0
     }
   #  if(P[x]<=3){                             #process 3:assuming a lagged over-flow  process(active for case 3)
    #   sur_R[x] =(Q[x] + P[x]) * k1 - Qmax - sub_R[x]    #lagged over-flow assuming a linear process
    # }
   }
   else{
     sur_R[x] = 0 
   }
  Q[x+1] = Q[x] + P[x] - sur_R[x] - sub_R[x] #process 4:balance equation for output
}