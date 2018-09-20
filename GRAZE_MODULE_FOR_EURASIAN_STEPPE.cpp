#include <stdio.h>



int main(void){
		 

			int i,j,k,l;
			float weight_init,weight;
			float NPPlive,NPPtotal,NPPdead;
			float buff[10];
			float NPPgraze[10];
			
			
			float sheep;
			long s_input;



	
			FILE *fa;
			FILE *ha;
			FILE *f;


			
			NPPdead = 0;
			NPPlive = NPPtotal;

			if((fa = fopen("NPP_2008.dat","ab+")) == NULL)
				printf("2008 input wrong");
		/*	if(fb = fopen("NPP_1998.dat") = NULL)
				printf("1998 input wrong");
			if(fc = fopen("NPP_1999.dat") = NULL)
				printf("1999 input wrong");
			if(fd = fopen("NPP_2000.dat") = NULL)
				printf("2000 input wrong");
			if(fe = fopen("NPP_2001.dat") = NULL)
				printf("2001 input wrong");
			if(ff = fopen("NPP_2002.dat") = NULL)
				printf("2002 input wrong");
			if(fg = fopen("NPP_2003.dat") = NULL)
				printf("2003 input wrong");
			if(fh = fopen("NPP_2004.dat") = NULL)
				printf("2004 input wrong");
			if(fj = fopen("NPP_2005.dat") = NULL)
				printf("2005 input wrong");
			if(fk = fopen("NPP_2006.dat") = NULL)
				printf("2006 input wrong");
			if(fl = fopen("NPP_2007.dat") = NULL)
				printf("2007 input wrong");
			if(fm = fopen("NPP_2008.dat") = NULL)
				printf("2008 input wrong");    */

			if((ha = fopen("sheep_2008.dat","ab+")) == NULL)
				printf("sheep_2008 input wrong");
			
			if((f = fopen("NPP_graze.dat","ab+")) == NULL)
				printf("NPPgraze input wrong");
			
			fprintf(f,"\n\n");
			for (j=0; j<=32; ++j){
				//for(k=0;k<j;++k)
				//	fscanf(fa,"%*[^\n]%*c"); 
			//	for(l=0;l<j;++l)
			//		fscanf(ha,"%*[^\n]%*c");    //跳行功能
				
				
					fscanf(fa,"%f	%f	%f	%f	%f",&buff[0], &buff[1], &buff[2], &buff[3], &buff[4]);
					fscanf(ha,"%f",&sheep);
					printf("%f ",sheep);
					weight = 40.0;
					
			for (i=0; i<5; ++i){
					
					NPPtotal = buff[i];
					printf("%f ",buff[i]);
				
					if (NPPtotal >= weight * sheep * 0.076 * 0.475)  //0.0361
						NPPgraze[i] = sheep * weight * 0.038;
					//NPPgraze = (float)sheep * (float)weight * 0.04 *0.475; //0.475为转换系数
					if (NPPtotal < weight * sheep * 0.076 * 0.475)   //0.0361
					//NPPgraze = (float)NPPtotal * 0.2;
						NPPgraze[i] = NPPtotal * 0.2;

					weight = (985 * weight + 1368 * weight * 0.038 + 947 * NPPdead / sheep) / 1000;  //这里需要添加死亡率和屠宰率
					//fwrite(&NPPgraze[i], sizeof(double),5,f);
					printf("%f\n", weight);
				
			}
			fprintf(f,"%f	%f	%f	%f	%f \n", NPPgraze[0], NPPgraze[1], NPPgraze[2], NPPgraze[3], NPPgraze[4]);
			}

					return 0;
			}
	