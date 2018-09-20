#include <stdio.h>
#include <math.h>

	main(void){

		float QMCtot, QECtot, EnzC1, EnzC2, DOC;
		float CUE,CN_m,CN_e,CN_1;
		float MBN,DON;
		float k_e,k_l,k_m,k_t,KK,k_d;
		float day,t,alpha;
		float Uc,Un,death;
		float EPC,EPC1,EPC2,ELC1,ELC2;
		float Re,Rm,Rg,Ro,DC1,DC2,DN1;
		float Mn,Rtot,MBCN;
		
		//start up values
		QMCtot = 1;
		EnzC1 = 0.01;
		EnzC2 = 0.01;
		QECtot = EnzC1 + EnzC2;
		MBN = QMCtot/CN_m;
		//In = 0;
		DOC = 0;
		DON = 0;
		day = 0; //start at day 0
		
		
		k_e = 0.05; //allocation to enzymes
		k_l = 0.05; //enzyme turnover rate
		k_m = 0.01; //maintainance respiration rate
		CUE = 0.5; //microbial C use efficiency
		k_t = 0.012; //biomass turnover rate 
		CN_m = 7.16; //microbial CN ratio
		CN_e = 7.16; //enzyme CN ratio
		KK = 0.3;  //half saturation constant of enzymes on substrates
		k_d = 1;     //max enzyme decomposition rate 
		CN_1 = 15;   //Substrate 1 CN ratio
		
		t = 1200;  //time step



		while (day < t){
		Uc = DOC;
		Un = DON;

		//Microbial fluxes
		death= k_t * QMCtot;
		//Enzymatical fluxes
		EPC = k_e * Uc;            //enzyme production
		Re = EPC * (1-CUE)/CUE;  //enzyme respiration associated with enzyme production
		Rm = k_m * QMCtot;      //maintainance respiration

		if (Uc < Rm + QECtot/CUE + ((Un - QECtot/CN_e)*CN_m/CUE)){
			alpha = 0.5;
		}
        else{
			alpha = (sqrt(((QECtot * QECtot) * QMCtot * k_m * CN_1 * CUE
	                 - 2 * (QECtot * QECtot) * CN_1 * CUE * k_d
     				 + (QECtot * QECtot) * CN_m * k_d
     			     + QECtot * KK * CN_m * k_d) 
					 * ((QECtot * QECtot) * QMCtot * k_m * CN_1 * CUE
	                 - 2 * (QECtot * QECtot) * CN_1 * CUE * k_d
     				 + (QECtot * QECtot) * CN_m * k_d
     			     + QECtot * KK * CN_m * k_d)
     				 - 4 * (QECtot * KK * QMCtot * k_m * CN_1 * CUE
     				 - QECtot * KK * CN_1 * CUE * k_d
     				 +KK * KK * QMCtot * k_m * CN_1 * CUE)
     				 *((QECtot * QECtot) * (-QMCtot) * k_m * CN_1 * CUE
     				 + 2 * (QECtot * QECtot) * CN_1 * CUE * k_d
     				 - QECtot * QECtot * CN_m * k_d))
     				 + (QECtot * QECtot) * (-QMCtot) * k_m * CN_1 * CUE
     				 + 2 * (QECtot * QECtot) * CN_1 * CUE * k_d 
     				 - (QECtot * QECtot) * CN_m * k_d 
     				 - QECtot * KK * CN_m * k_d)
     			     / (2 * ((QECtot * QECtot) * (-QMCtot) * k_m * CN_1 * CUE
                       + 2 * (QECtot * QECtot) * CN_1 * CUE * k_d 
     				 - (QECtot * QECtot) * CN_m * k_d));
		}

  		
		if (alpha > 1) alpha = 1;
			

			 EPC1 = EPC * alpha;
			 EPC2 = EPC * (1 - alpha);   //enzyme 1 and 2 production


			 ELC1 = k_l * EnzC1;
			 ELC2 = k_l * EnzC2;        //enzyme 1 and 2 turnover

			 DC1 = (EnzC1*k_d) / (KK + EnzC1);     //DOC1 production
			 DC2 = (EnzC2*k_d) / (KK + EnzC2);     //DOC2 production
			 DN1 = DC1/CN_1;

		if (Uc < Rm + EPC/CUE + ((Un - EPC/CN_e)*CN_m/CUE)) {
			 Rg= (Uc - EPC/CUE - Rm)*(1-CUE);
			 Ro=0;
			 Mn= (Un) - (EPC/CN_e) - ((Uc - Rm - (EPC/CUE))*CUE/CN_m);    //C is not enough
			}
		else {
			 Rg= (Un - EPC/CN_e)*CN_m*(1-CUE)/CUE;                        //N is not enough
			 Ro= Uc - Rm - EPC/CUE - (Un - EPC/CN_e) * CN_m/CUE;
			 Mn= 0; 
			}

		 //sum across respiration fluxes to get total respiration flux
			 Rtot = Re + Rm + Rg + Ro;                             
  
		//pools! Update biomass C and N pools, dissolved organic C and N pools, enzyme pools, and the time step. MBCN is calculated to make sure stoichiometry is not being violated
			 QMCtot = QMCtot + Uc - death - EPC - Re - Rm - Rg - Ro;
			 MBN = MBN + Un - death/CN_m - EPC/CN_e - Mn;	
			 DOC = DOC + DC1 + DC2  - Uc; 
			 DON = DON + DN1  - Un;
			 EnzC1= EnzC1 + EPC1 - ELC1;
			 EnzC2= EnzC2 + EPC2 - ELC2;
			 QECtot = EnzC1 + EnzC2;
			 MBCN = QMCtot/MBN;
			 day = day + 1;


			 printf("QMCtot = %f\n",QMCtot);
			 printf("MBN = %f\n",MBN);
		}
			return 0;
	}