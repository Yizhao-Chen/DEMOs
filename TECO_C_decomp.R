#preset C input
npp1 = 30
npp2 = 50

#preset soil moisture and temperature scalars
ft = 0.5
fw = 0.6

#preset C transition rate between the C pools
fml_f = 0.2
fsl_f = 0.3
fsl_s = 0.4
ff_s = 0.35
ff_p = 0.2
fs_f = 0.15
fs_p = 0.15
fp_f = 0.5

#preset potential decomposition rates
k_ml = 0.67
k_sl = 0.26
k_f  = 1.25
k_s  = 0.2
k_p  = 0.004

#preset initial C pool sizes
C_ml1 = 100
C_sl1 = 100
C_f1 = 50
C_s1 = 500
C_p1 = 1000

#Modeling the soil C dynamics
for (i in 1:100){

  dCml = k_ml * ft * fw * C_ml1
  dCsl= k_sl * ft * fw * C_sl1
  dCf = k_f * ft * fw * C_f1
  dCs = k_s * ft * fw * C_s1
  dCp = k_p * ft * fw * C_p1

  dCml_f = dCml * fml_f
  
  dCsl_f = dCsl * fsl_f
  dCsl_s = dCsl * fsl_s
  
  dCf_s = dCf * ff_s
  dCf_p = dCf * ff_p
  
  dCs_f = dCs * fs_f
  dCs_p = dCs * fs_p
  
  dCp_f = dCp * fp_f
  
  dCml_emt = dCml * (1 - fml_f);
  dCsl_emt = dCsl * (1 - fsl_f - fsl_s)
  dCf_emt = dCf * (1 - ff_s - ff_p)
  dCs_emt = dCs * (1 - fs_f - fs_p)
  dCp_emt = dCp * (1 - fp_f)
  

  C_ml1 = C_ml1 - dCml + npp1;
  C_sl1 = C_sl1 - dCsl + npp2;
  C_f1 = C_f1 - dCf + dCml_f + dCsl_f + dCs_f + dCp_f;
  C_s1 = C_s1 - dCs + dCsl_s + dCf_s;
  C_p1 = C_p1 - dCp + dCf_p + dCs_p;
  Rh = dCml_emt + dCsl_emt + dCf_emt + dCs_emt + dCp_emt;
}
  