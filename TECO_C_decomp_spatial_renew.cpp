#include <stdio.h>
#include <math.h>

	main(void){

//定义变量
	int jday;   //i
	float ft,fw;    //土壤水分和温度系数
	float k_ml,k_sl,k_f,k_s,k_p;     //潜在分解速率
	float C_ml[4500],C_sl[4500], C_f[4500], C_s[4500], C_p[4500];       //状态变量 碳库大小
	float dCml[4500],dCsl[4500],dCf[4500], dCs[4500],dCp[4500];         //单位时间步长碳库变化
	float dCml_f[4500], dCsl_f[4500],dCsl_s[4500],dCf_s[4500],dCf_p[4500],dCs_f[4500],dCs_p[4500], dCp_f[4500];    //单位时间步长分解传输
	float dCml_emt[4500],dCsl_emt[4500],dCf_emt[4500],dCs_emt[4500],dCp_emt[4500];      //单位时间步长分解排放
	float fml_f,fsl_f,fsl_s,ff_s,ff_p,fs_f,fs_p,fp_f;    //传输系数
//	float Rh,npp1,npp2;    //总异养呼吸 npp输入
	float Rh[4500];


//for spatial analysis
	int i;
	int pixel = 4500;
	int pix;
	short n_input[4500];
	float npp1[4500];
	float npp2[4500];



	FILE *NPP;
	FILE *TEMP;
	FILE *PREP;
	FILE *Rh_output;   //输入输出文件定义

	   if((NPP=fopen("C:\\Users\\dell\\Desktop\\class_11_28\\cnpp2000_3611.dat","rb"))==NULL)
		{
        printf("Can not open the file %s\n",NPP);    //从NPP文件中打开NPP
	  }
	   if((TEMP=fopen("C:\\Users\\dell\\Desktop\\class_11_28\\temp2000.img","rb"))==NULL)
		{	
        printf("Can not open the file %s\n",TEMP);    //从NPP文件中打开Tempertaure
	  }
	   if((PREP=fopen("C:\\Users\\dell\\Desktop\\class_11_28\\prep2000.img","rb"))==NULL)
		{
        printf("Can not open the file %s\n",PREP);    //从NPP文件中打开Precipitation
	  }
	   if((Rh_output=fopen("C:\\Users\\dell\\Desktop\\class_11_28\\Rh_output.img","ab+"))==NULL)
		{
        printf("Can not open the file %s\n",Rh_output);    //从NPP文件中打开Rh输出文件
	  }


	   

for (i=0;i<2250;i++){                              //行循环
	fread(&n_input[0],sizeof(short),pixel,NPP);             
	for(pix=0;pix<pixel;pix++) {                   //像元循环
			//	printf("n_input = %d\n", n_input[pix]);
				npp1[pix] = (float)n_input[pix] * 0.4;
				npp2[pix] = (float)n_input[pix] * 0.6;
			//	printf("npp1 = %f\n",npp1[pix]);
			//	printf("npp2 = %f\n",npp2[pix]);

					ft = 0.5;
					fw = 0.6;     //environmental scalars    直接赋值

						//碳库传输系数
					fml_f = 0.2;    //Metabolic litter -> fast soil
					fsl_f = 0.3;    //structure litter -> fast soil
					fsl_s = 0.4;    //structure litter -> slow soil
					ff_s = 0.35;    //fast soil -> slow soil
					ff_p = 0.2;     //fast soil -> passive soil
					fs_f = 0.15;    //slow soil -> fast soil
					fs_p = 0.15;    //slow soil -> passive soil
					fp_f = 0.5;      //passive soil -> fast soil
	
	
	//潜在分解速率
					k_ml = 0.67;     //metabolic litter potential decomposition rate
					k_sl = 0.26;     //structure litter 
					k_f  = 1.25;     //fast 
					k_s  = 0.2;      //slow
					k_p  = 0.004;    //passive
	
					C_ml[pix] = 100;
					C_sl[pix] = 100;
					C_f[pix] = 50;
					C_s[pix] = 500;
					C_p[pix] = 1000;     //原始碳库大小  直接赋值

	for (jday = 0;jday < 100;jday++){     //循环100次       
//C loss for each pool    每个库的碳库损失
	dCml[pix] = k_ml * ft * fw * C_ml[pix];    
	dCsl[pix]= k_sl * ft * fw * C_sl[pix];
	dCf[pix] = k_f * ft * fw * C_f[pix];
	dCs[pix] = k_s * ft * fw * C_s[pix];
 	dCp[pix] = k_p * ft * fw * C_p[pix];

//C input for each pool   碳库输入
	dCml_f[pix] = dCml[pix] * fml_f;

	dCsl_f[pix] = dCsl[pix] * fsl_f;
	dCsl_s[pix] = dCsl[pix] * fsl_s;

	dCf_s[pix] = dCf[pix] * ff_s;
	dCf_p[pix] = dCf[pix] * ff_p;

	dCs_f[pix] = dCs[pix] * fs_f;
	dCs_p[pix] = dCs[pix] * fs_p;

	dCp_f[pix] = dCp[pix] * fp_f;

//CO2 emission for each pool    碳库排放
	dCml_emt[pix] = dCml[pix] * (1 - fml_f);
	dCsl_emt[pix] = dCsl[pix] * (1 - fsl_f - fsl_s);
	dCf_emt[pix] = dCf[pix] * (1 - ff_s - ff_p);
	dCs_emt[pix] = dCs[pix] * (1 - fs_f - fs_p);
	dCp_emt[pix] = dCp[pix] * (1 - fp_f);

//C pool sizes updates        碳库更新
	C_ml[pix] = C_ml[pix] - dCml[pix] + npp1[pix];
	C_sl[pix] = C_sl[pix] - dCsl[pix] + npp2[pix];
	C_f[pix] = C_f[pix] - dCf[pix] + dCml_f[pix] + dCsl_f[pix] + dCs_f[pix] + dCp_f[pix];
	C_s[pix] = C_s[pix] - dCs[pix] + dCsl_s[pix] + dCf_s[pix];
	C_p[pix] = C_p[pix] - dCp[pix] + dCf_p[pix] + dCs_p[pix];
	Rh[pix] = dCml_emt[pix] + dCsl_emt[pix] + dCf_emt[pix] + dCs_emt[pix] + dCp_emt[pix];	
	}
	}
	fwrite(&Rh[0],sizeof(float),pixel,Rh_output); 
}
	//npp1 = 30;
	//npp2 = 50;     //npp输入  直接赋值
	

	return 0;
	}	