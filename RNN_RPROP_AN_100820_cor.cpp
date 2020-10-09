/* 05.05.2020*/
//RNN 1 layer
//iRPROP-
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <fcntl.h>
#include <process.h>
#include <sys\stat.h>
#include <io.h>

int main()
{
static long ip,p;
static double r2,r1,r,r3,r4,r5,r6,r7,del3[3000],tt[20],ttt[20];
static int i2,i1,i_count1,ii,j1,jj,i10,j2,i111;
static double sum,sum3,amin;
static int ipp,i,j,i3,l4,i_sm[2000],ill,ippp,imin,i_count2;
static double s1[3000],s3[3000];
static double x[3000],x1[3000],x3[3000],x11[3000],ap,min,min3,x4[3000];
static int jsum,nb;

static int k,k1,i_max, i_volume,i_string,i_representation;

static char  smiles[2000];
static char  buf1[8000000];

static double rr1,rr2,delta_max,delta_min,eta_plus,eta_minus,delta0,rr3,rr4,rrr1,rrr2;


double (*w1)[3000];
double (*w1p)[3000];
double (*w3)[3000];
double (*s_smile)[3000];
double (*del1x)[3000];
double (*delta1x)[3000];
double (*deltaw1x)[3000];
double (*del1p)[3000];
double (*delta1p)[3000];
double (*deltaw1p)[3000];
double (*del3x)[3000];
double (*delta3x)[3000];
double (*deltaw3x)[3000];
	double (*del11)[3000];
	double (*del12)[3000];
	double (*del33)[3000];
   
   w1=new double[3000][3000];
   w1p=new double[3000][3000];
   w3=new double[3000][3000];
   s_smile=new double[3000][3000];
   del1x=new double[3000][3000];
   delta1x=new double[3000][3000];
   deltaw1x=new double[3000][3000];
   del1p=new double[3000][3000];
   delta1p=new double[3000][3000];
   deltaw1p=new double[3000][3000];
   del3x=new double[3000][3000];
   delta3x=new double[3000][3000];
   deltaw3x=new double[3000][3000];
	   del11=new double[3000][3000];
	   del12=new double[3000][3000];
	   del33=new double[3000][3000];
      
static char  buf[8000000],c[20];

static float stat[8000],stat3[8000],d[1000],sigma,sigma3;
static float s_eps[3000];
static int i_count,i_count11,i_count33,i_count3,l1,l2,l3;
static int i_activation;

     FILE *stream_Z;
     FILE *stream1;
     FILE *stream2;
     FILE *stream3;
     FILE *stream;
     
printf("The name of the SMILES file in .dat format \n");
scanf("%s",smiles);
//   if ((stream = fopen(&smiles[0], "rb")) == NULL)
   if ((stream = fopen("smiles_mod.dat", "rb")) == NULL)
   {
      fprintf(stderr, "Cannot open input file.\n");
      return 1;
   }

printf("Introduce type of an activation function, 1-Tanh | 2-Sigmoid |3-RELU \n");
scanf("%d",&i_activation);
printf("activation %d",i_activation);
   /* open a file for update */
   stream_Z = fopen("eps.dat", "r");

         /* open a file */

   stream1 = fopen("d1_d_SIGMOID20_RPROP_check.dat", "w");/* RMSE vs epoch for test pool*/
   stream2 = fopen("d2_d_SIGMOID20_RPROP_check.dat", "w"); /* RMSE vs epoch for training pool*/
   stream3 = fopen("d3_d_SIGMOID20_RPROP_check.dat", "w"); /* Predicted eps*/

//__Initialization of the working registers___
   delta0=0.015; /*parameter for optimization*/
   /*parameter for iPROP-*/
   delta_max=50.0;
   delta_min=0.000001;
   eta_plus=1.2;
   eta_minus=0.5;

   i_count2=0;
   amin=10000.;
   imin=0;
   min=1000.;
   min3=1000.;

   rrr1=delta0;

//________Initialization___________
for(j=0;j<3000;j++)
{
	for(i=0;i<3000;i++)
	{
	del1x[j][i]=0.;
	delta1x[j][i]=delta0;
	deltaw1x[j][i]=delta0;
		del3x[j][i]=0.;
		delta3x[j][i]=delta0;
		deltaw3x[j][i]=delta0;
			del1p[j][i]=0.;
			delta1p[j][i]=delta0;
			deltaw1p[j][i]=delta0;
	}//i
}//j
  //___For reading eps data___
   c[0]=48;
   c[1]=49;
   c[2]=50;
   c[3]=51;
   c[4]=52;
   c[5]=53;
   c[6]=54;
   c[7]=55;
   c[8]=56;
   c[9]=57;

   tt[0]=1.;
   tt[1]=10.;
   tt[2]=100.;
   tt[3]=1000.;
   tt[4]=10000.;

   ttt[0]=0.1;
   ttt[1]=0.01;
   ttt[2]=0.001;
   ttt[3]=0.0001;
   ttt[4]=0.00001;
   ttt[5]=0.000001;
   ttt[6]=0.0000001;
   ttt[7]=0.00000001;
   ttt[8]=0.000000001;
   ttt[9]=0.0000000001;
   ttt[10]=0.00000000001;
   ttt[11]=0.000000000001;
   ttt[12]=0.0000000000001;
   ttt[13]=0.00000000000001;
   ttt[14]=0.000000000000001;
   ttt[15]=0.0000000000000001;
   ttt[16]=0.00000000000000001;
   ttt[17]=0.000000000000000001;
   ttt[18]=0.0000000000000000001;
//****** INITIALIZATION *********
ii=0;
i_max=0;
//___SMILES decoding (ASCII to binary)_____
//1._____ Reading of SMILE array_____
nb=400000;
fread(buf,nb,1,stream);		//SMILE in BUF

//2._____VOLUME ESTIMATION _____
i_volume=0;
i_string=0;
count:
	if(buf[i_volume]==10){i_string=i_string+1;}	//"10"&"0" END OF STRING
	if((buf[i_volume]==10)&(buf[i_volume+1]==0)){goto count1;}	//"10"&"0" END OF FILE
	i_volume=i_volume+1;
	goto count;
count1:
printf("\n Volume= %4d",i_volume); 	//VOLUME in i_volume
printf("\n NUMBER of STRINGS= %4d",i_string); 	//VOLUME in i_volume
//_____END VOLUME ESTIMATION _____


//3._________ MAX SMILE LENGTH CALCULATION _______
   i1=0;
cont3s:
	i_count=0.;
cont1s:
   if(buf[i1]==10) {goto cont2s;}	//"10" END OF STRING
   i1=i1+1;
   i_count=i_count+1;
   goto cont1s;
cont2s:
if(i_max<i_count) {i_max=i_count;}
//printf("\n %d i_max=  %d",i1,i_max);
//getch();
if(i1==i_volume){goto cont4s;}
   i1=i1+1;
	goto cont3s;
cont4s:
printf("\n i_max=  %d",i_max);	//MAX 0f STRING SMILE in i_max (ASCII symbols)
getch();
//_________ END  MAX SMILE CALCULATION _______
//4._____________ SMILE BINARY REPRESENTATION  _______
	ii=0;
   i1=0;
cont3:
	i_count=0.;
cont1:
   if(buf[i1]==10) {goto cont2;}
   i1=i1+1;
   i_count=i_count+1; 	//IN i_count the LENGTH (in ASCCI symbols) of string SMILE
   goto cont1;

cont2:
//3. ____*************** CONDITION ************______
//ii=0;
	for(i3=0;i3<i_count;i3++)
   {
   k=buf[i1-i_count+i3];
   	k1=k-128;
      if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
	   	k1=k-64;
   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
	   		k1=k-32;
	   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
		   		k1=k-16;
		   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
			   		k1=k-8;
			   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
				   		k1=k-4;
				   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
					   		k1=k-2;
					   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;
						   		k1=k-1;
						   	   if(k1>=0) {buf1[ii]=1;k=k1;} else{buf1[ii]=-1;}ii=ii+1;

	}//i3

	for(i3=i_count;i3<i_max;i3++)
   {
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
   buf1[ii] = 0; ii = ii+1;
	}//i3


if(i1==i_volume){goto cont4;} //CONDITION "END OF FILE"

   i1=i1+1;
goto cont3;
//_____________END SMILE BINARY REPRESENTATION  _______


cont4:
printf("\n The start of the processing");
//getch();

for(i=0;i<i_string;i++)
{
	for(i1=0;i1<i_max*8;i1++)
	{
   s_smile[i][i1]=(double)(buf1[i*i_max*8+i1]);
   }//i1
}//i

//________________ARRAY FOR EPS __________________
nb=8000000;
fread(buf,nb,1,stream_Z);

//_______ Decoding of array ______

i2=0;
i1=0;
mn2:
i_count1=0;
mn:
ii=buf[i1];if(ii==46) {j1=i_count1;}
ii=buf[i1];if(ii==10) {i1=i1+1;i_count1=i_count1+1;goto mn1;}

i1=i1+1;
i_count1=i_count1+1;
goto mn;

mn1:
//1.				//SAMPLE
i3=buf[i1-i_count1+j1];

r2=1.;
r=0.;
for(i=0;i<j1;i++)
{
i3=buf[i1-i_count1+j1-i-1];
//printf("\n %4d %d",i,i3);
//getch();
if(i3==48){r1=0.;r=r+r1*tt[i];}
if(i3==49){r1=1.;r=r+r1*tt[i];}
if(i3==50){r1=2.;r=r+r1*tt[i];}
if(i3==51){r1=3.;r=r+r1*tt[i];}
if(i3==52){r1=4.;r=r+r1*tt[i];}
if(i3==53){r1=5.;r=r+r1*tt[i];}
if(i3==54){r1=6.;r=r+r1*tt[i];}
if(i3==55){r1=7.;r=r+r1*tt[i];}
if(i3==56){r1=8.;r=r+r1*tt[i];}
if(i3==57){r1=9.;r=r+r1*tt[i];}
if(i3==45){r2=-1.;}
}

for(i=0;i<i_count1-j1-2;i++)
{
i3=buf[i1-i_count1+j1+i+1];
if(i3==48){r1=0.;}
if(i3==49){r1=1.;}
if(i3==50){r1=2.;}
if(i3==51){r1=3.;}
if(i3==52){r1=4.;}
if(i3==53){r1=5.;}
if(i3==54){r1=6.;}
if(i3==55){r1=7.;}
if(i3==56){r1=8.;}
if(i3==57){r1=9.;}
r=r+r1*ttt[i];
}

s_eps[i2]=r2*r;
printf("\n++ %4d %20.18f",i2,s_eps[i2]);
//getch();

i2=i2+1;
if(i2<i_string) {goto mn2;}		// NEW Sample

//getch();

//___VERIFICATION OF THE PROCESSING DATA (CHECKING FOR THE DUBLICATES)_____
for(j=0;j<i_string-1;j++)
{
	for(i=j+1;i<i_string;i++)
	{
   i10=0;
		for(i1=0;i1<i_max*8;i1++)
		{
      if(s_smile[j][i1]!=s_smile[i][i1]) {i10=1;}
      }
if(i10==0)
{
s_eps[i]=s_eps[j];
}
   }//i
}//j

//________________PREPARATION OF THE TEST POOL___________
ippp=1;
		for(i1=0;i1<i_string;i1++)
		{
      i_sm[i1]=-1;
      }

		for(i1=0;i1<(int)(0.05*i_string);i1++)
		{
      i_sm[i1]=10+15*i1;
      }

printf("\n Introduce type of SMILES representation, 1-binary | 2- decimal");
scanf("%d",&i_representation);
//printf("activation %d",i_representation);

if (i_representation == 1)
{
i_max = i_max *8;
goto iter_bin;
}
//********************* decimal SMILES representation****************************
for (i1=0 ; i1<i_string ; i1++)
{
  for (i=0 ; i<i_max ; i++)			//1136:8=142
  {
  r7=s_smile[i1][i*8];
  if(r7<0.){r7=0.;}
	  r6=s_smile[i1][i*8+1];
     if(r6<0.){r6=0.;}
		  r5=s_smile[i1][i*8+2];
	     if(r5<0.){r5=0.;}
			  r4=s_smile[i1][i*8+3];
		     if(r4<0.){r4=0.;}
				  r3=s_smile[i1][i*8+4];
			     if(r3<0.){r3=0.;}
					  r2=s_smile[i1][i*8+5];
				     if(r2<0.){r2=0.;}
						  r1=s_smile[i1][i*8+6];
					     if(r1<0.){r1=0.;}
							  r=s_smile[i1][i*8+7];
						     if(r<0.){r=0.;}
  r=r7*128.+r6*64.+r5*32.+r4*16.+r3*8.+r2*4.+r1*2.+r;
  s_smile[i1][i]=r-32.;
  }
}//i1

iter_bin:
//_________________________ LEARNING iRPROP-___________________________
// ___________________ INITIALIZATION _________________________
// 
//First Layer
l1=i_max;
l2=i_max;
l3=1;
l4=1;

//First Layer
for(j=0;j<l1;j++)
{
  for (i=0 ; i<l1 ; i++)
  {
  w1[j][i]=2./sqrt(1000.)*(0.5-(double)(rand()/32768.));
  }
}

//Output Layer
for(j=0;j<l3;j++)
{
  for (i=0 ; i<l1 ; i++)
  {

  w3[j][i]=2./sqrt(1000.)*(0.5-(double)(rand()/32768.));

  }
}

//Context Unit Layer
for(j=0;j<l1;j++)
{
  for (i=0 ; i<l1 ; i++)
  {

  w1p[j][i]=2./sqrt(1000.)*(0.5-(double)(rand()/32768.));

  }
}
  for (i=0 ; i<l1 ; i++)	//RECURRENT
  {
  x1[i]=0.;
  }

  for (i=0 ; i<l4 ; i++)	//RECURRENT
  {
  x3[i]=0.;
  }

// _________________ END FOR INITIALIZATION ____________________


j2=0;
do		//__________________________________________________________
{
ipp=ipp+1;
p=p+1;
jsum=jsum+1;


for(j=0;j<i_string;j++)
{
	for(i=0;i<i_string;i++)
	{
    del11[j][i]=0.;
    del12[j][i]=0.;
    del33[j][i]=0.;
   }
}
rrr2=0.;

// ********************* iRPROP ************************

//The generating training seguence

for(i111=0;i111<i_string;i111++)   //_______________________________ B E G I N I N G
{
//___Selection of the learning pool_______
ill=0;
for(i=0;i<i_string/ippp;i++)

{

if(i111==i_sm[i]) {goto iter3;}
}


d[0]=s_eps[i111];		/*Original eps data*/


// INPUT
  for (i=0 ; i<l1 ; i++)			//A
  {
  x[i]=s_smile[i111][i];
  }

//********  The calculation of s[] ***********
//for the first layer
for(j=0;j<l1;j++)
{
  s1[j]=0.;
    for(i=0;i<l1;i++)
    {
    s1[j]=s1[j]+w1[j][i]*x[i];
    }

	    for(i=0;i<l1;i++)	//RECURRENT
   	 {
	    s1[j]=s1[j]+w1p[j][i]*x1[i];
   	 }
if (i_activation == 2)
{
//SIGMOID
r=s1[j];
if(r>15.){r=15.;}
if(r<-15.){r=-15.;}
    x11[j]=1./(1.+exp(-r));
}
if (i_activation == 1)
{
//tanh
r=s1[j];
x11[j]=tanh(r);
}
}//j



//for the output layer
for(j=0;j<l3;j++)
{
  s3[j]=0.;
    for(i=0;i<l1;i++)
    {
    s3[j]=s3[j]+w3[j][i]*x11[i];
    }
    x3[j]=s3[j];// output
}



//****************************************************************************
//****************************************************************************
// The del3 calculation
for(i=0;i<l3;i++)
{
del3[i]=(x3[i]-d[0]);
}

rrr2=rrr2+del3[0]*del3[0];


	for(j=0;j<l1;j++)
	{
//	x1[j]=x11[j];
	}


//______ W1P ______
for(j=0;j<l1;j++)
{
  for (i=0 ; i<l1 ; i++)
  {
  if (i_activation==2)
  {
  del12[j][i]=del12[j][i]+del3[0]*w3[0][j]*x11[j]*(1.-x11[j])*x1[i];	//sigmoid
  }
  if (i_activation == 1)
  {
  del12[j][i]=del12[j][i]+del3[0]*w3[0][j]*((1.-x11[j]*x11[j]))*x1[i];	//tanh
  }
//	printf("\n___ %d j= %d i1= %d %f",i111,j,i,del11[j][i]);
  }
//	getch();
}
//	getch();

	for(j=0;j<l1;j++)
	{
	x1[j]=x11[j];
	}




//______ W1 ______
for(j=0;j<l1;j++)
{
  for (i=0 ; i<l1 ; i++)
  {
  if (i_activation==2)
  {
  del11[j][i]=del11[j][i]+del3[0]*w3[0][j]*(x1[j]*(1.-x1[j]))*x[i];//sigmoid
  }
  if (i_activation == 1)
  {
  del11[j][i]=del11[j][i]+del3[0]*w3[0][j]*((1.-x1[j]*x1[j]))*x[i];//tanh
  }
//	printf("\n___ %d j= %d i1= %d %f",i111,j,i,del11[j][i]);
  }
//	getch();
}
//	getch();



//_______W3_______
  for (i=0 ; i<l2 ; i++)
  {
  del33[0][i]=del33[0][i]+del3[0]*x1[i];
  }


iter3:	//_____________________________________________________ E N D BEGINING

}//i111

	printf("\n+++++ %f",rr2);
//   getch();

//*************************  iRPROP himself **************************
//_____________ 1 ______________

for(j=0;j<l1;j++)
{
  for (i=0 ; i<l1 ; i++)
  {
  rr1=del1x[j][i];			//dE/dWij(t-1)
  rr2=del11[j][i];        //dE/dWij(t)


//______ 1 ______
		if(rr1*rr2>0.)
      {
      rr3=delta1x[j][i]*eta_plus; if(rr3>delta_max){rr3=delta_max;} delta1x[j][i]=rr3;//
      rr4=1.; if(rr2<0.) {rr4=-1.;}		//sign
      deltaw1x[j][i]=-rr4*delta1x[j][i];
      w1[j][i]=w1[j][i]+deltaw1x[j][i];
      del1x[j][i]=del11[j][i];
      }//if

//2
		if(rr1*rr2<0.)
      {
      rr3=delta1x[j][i]*eta_minus; if(rr3<delta_min){rr3=delta_min;} delta1x[j][i]=rr3;//
      if(rrr2>rrr1) {w1[j][i]=w1[j][i]-deltaw1x[j][i]*0.;}
      del1x[j][i]=0.;
      }//if

// 3
		if(rr1*rr2==0.)
      {
      rr4=1.; if(rr2<0.) {rr4=-1.;}	  if(rr2==0.) {rr4=0.;}	//sign
      deltaw1x[j][i]=-rr4*delta1x[j][i];
      w1[j][i]=w1[j][i]+deltaw1x[j][i];
      del1x[j][i]=del11[j][i];
      }//if

//      del1x[j][i]=del11[j][i];

  }//i
}//j

//_____________ 1P ______________

//Context Unit Layer
for(j=0;j<l2;j++)
{
  for (i=0 ; i<l1 ; i++)
  {
  rr1=del1p[j][i];			//dE/dWij(t-1)
  rr2=del12[j][i];        //dE/dWij(t)
//1
		if(rr1*rr2>0.)
      {
      rr3=delta1p[j][i]*eta_plus; if(rr3>delta_max){rr3=delta_max;} delta1p[j][i]=rr3;//
      rr4=1.; if(rr2<0.) {rr4=-1.;}		//sign
      deltaw1p[j][i]=-rr4*delta1p[j][i];
      w1p[j][i]=w1p[j][i]+deltaw1p[j][i];
      del1p[j][i]=del12[j][i];
      }//if

//2
		if(rr1*rr2<0.)
      {
      rr3=delta1p[j][i]*eta_minus; if(rr3<delta_min){rr3=delta_min;} delta1p[j][i]=rr3;//
      if(rrr2>rrr1) {w1p[j][i]=w1p[j][i]-deltaw1p[j][i]*0.;}
      del1p[j][i]=0.;
      }//if

//3
		if(rr1*rr2==0.)
      {
      rr4=1.; if(rr2<0.) {rr4=-1.;}	if(rr2==0.) {rr4=0.;}	//sign
      deltaw1p[j][i]=-rr4*delta1p[j][i];
      w1p[j][i]=w1p[j][i]+deltaw1p[j][i];
      del1p[j][i]=del12[j][i];
      }//if

//      del1p[j][i]=del12[j][i];
  }//i
}//j



//_________ 3 __________
for(j=0;j<l3;j++)
{
  for (i=0 ; i<l2 ; i++)
  {
  rr1=del3x[j][i];			//dE/dWij(t-1)
  rr2=del33[j][i];        //dE/dWij(t)
//1
		if(rr1*rr2>0.)
      {
      rr3=delta3x[j][i]*eta_plus; if(rr3>delta_max){rr3=delta_max;} delta3x[j][i]=rr3;//
      rr4=1.; if(rr2<0.) {rr4=-1.;}		//sign
      deltaw3x[j][i]=-rr4*delta3x[j][i];
      w3[j][i]=w3[j][i]+deltaw3x[j][i];
      del3x[j][i]=del33[j][i];
      }//if

//2
		if(rr1*rr2<0.)
      {
      rr3=delta3x[j][i]*eta_minus; if(rr3<delta_min){rr3=delta_min;} delta3x[j][i]=rr3;
      if(rrr2>rrr1) {w3[j][i]=w3[j][i]-deltaw3x[j][i]*0.;}
      del3x[j][i]=0.;
      }//if


//3
		if(rr1*rr2==0.)
      {
      rr4=1.; if(rr2<0.) {rr4=-1.;}	  if(rr2==0.) {rr4=0.;}	//sign
      deltaw3x[j][i]=-rr4*delta3x[j][i];
      w3[j][i]=w3[j][i]+deltaw3x[j][i];
      del3x[j][i]=del33[j][i];
      }//if

//      del3x[j][i]=del33[j][i];
  }//i
}//j


rrr1=rrr2;

//_______________________ Epoch-dependent RMSE calculation _______

if((ipp%1)==0)
{
i_count2=i_count2+1;


for(j=0;j<l1;j++)
{
x4[j]=x1[j];
}


printf("\n");
i_count=0;
i_count3=0;
sum=0.;
sum3=0.;


for(jj=0;jj<i_string;jj++)	//________________________ B E G I N I N G
{
ill=0;
for(i=0;i<1270/ippp;i++)
{
if(jj==i_sm[i]) {ill=1;}
}

d[0]=s_eps[jj];


// INPUT
  for (i=0 ; i<l1; i++)
  {
  x[i]=s_smile[jj][i];
  }

//for the first layer
for(j=0;j<l1;j++)
{
  s1[j]=0.;
    for(i=0;i<l1;i++)
    {
    s1[j]=s1[j]+w1[j][i]*x[i];
    }

//for the recurrent layer
	   for(i=0;i<l1;i++)
   	{
    	s1[j]=s1[j]+w1p[j][i]*x4[i];
      }

if (i_activation == 2)
{
//Sigmoid
r=s1[j];
if(r>15.){r=15.;}
if(r<-15.){r=-15.;}
    x11[j]=1./(1.+exp(-r));
}
if (i_activation == 1)
{
//tanh
r=s1[j];
x11[j]=tanh(r);
}
}//j

if(ill==0)
{
	for(j=0;j<l1;j++)
	{
	x4[j]=x11[j];
	}
}


//for the output layer
for(j=0;j<l3;j++)
{
  s3[j]=0.;
    for(i=0;i<l1;i++)
    {
    s3[j]=s3[j]+w3[j][i]*x11[i];
    }
    x3[j]=s3[j];// output
}//j


	ill=0;
	for(i=0;i<i_string/ippp;i++)
	{
	if(jj==i_sm[i]) {ill=1;}
	}

if(ill==1){stat[i_count]=x3[0];sum=sum+x3[0];i_count=i_count+1;} /*For the test pool*/
if(ill==0){stat3[i_count3]=x3[0];sum3=sum3+x3[0];i_count3=i_count3+1;}/*For the learning pool*/


iter31:

}//jj	_______________________________ E N D    BEGINING

printf("\n___ i_count= %d %d",i_count,i_count3);

sum=sum/i_count;
sum3=sum3/i_count3;

//__________ RMSE calculation for the test and learning pools_____________
//__________ 1,2 _____________

sigma=0.;
sigma3=0.;
i_count11=0;
i_count33=0;
for(i=0;i<i_string;i++)	//________________________________________________________
{

	ill=0;
	for(i1=0;i1<i_string/ippp;i1++)
	{
	if(i==i_sm[i1]) {ill=1;}
	}

if(ill==1) {sigma=sigma+(stat[i_count11]-s_eps[i])*(stat[i_count11]-s_eps[i]);i_count11=i_count11+1;}  /*RMSE for the test pool*/
if(ill==0) {sigma3=sigma3+(stat3[i_count33]-s_eps[i])*(stat3[i_count33]-s_eps[i]);i_count33=i_count33+1;}  /*RMSE for the learning pool*/

iter10:
}//____________________________________________________________________________

sigma=sigma/i_count11;
sigma3=sigma3/i_count33;
printf("\n average= %f sigma= %f",sum, sqrt(sigma));
printf("\n average= %f sigma3= %f",sum3, sqrt(sigma3));

r=sqrt(sigma);
if(min>r) {min=r;}

r=sqrt(sigma3);
if(min3>r) {min3=r;imin=ipp;}

printf("\n %d i_count11= %d i_count33= %d min= %f min3= %f",i_count2,i_count11,i_count33,min,min3);
//getch();
//goto iter4;

r=sqrt(sigma);
fprintf(stream1, "\n %f",r);


r=sqrt(sigma3);
fprintf(stream2, "\n %f",r);


}//if

   ip=ip+1;
}while(i_count2!=500);

//***************** END OF THE LEARNING PROCEDURE (500 EPOCHS) ***************************
//___________Resulted implementation of RRN_______

{
for(j=0;j<l1;j++)
{
x4[j]=x1[j];
}


printf("\n");
i_count=0;
i_count3=0;
sum=0.;
sum3=0.;


for(jj=0;jj<i_string;jj++)
{
ill=0;
for(i=0;i<i_string/ippp;i++)
{
if(jj==i_sm[i]) {ill=1;}
}
  d[0]=s_eps[jj];

// INPUT
  for (i=0 ; i<l1; i++)
  {
  x[i]=s_smile[jj][i];
  }

//for the first layer
for(j=0;j<l1;j++)
{
  s1[j]=0.;
    for(i=0;i<l1;i++)
    {
    s1[j]=s1[j]+w1[j][i]*x[i];
    }
	   for(i=0;i<l1;i++)
   	{
    	s1[j]=s1[j]+w1p[j][i]*x4[i];
      }

if (i_activation == 2)
{
//SIGMOID
r=s1[j];
if(r>15.){r=15.;}
if(r<-15.){r=-15.;}
    x11[j]=1./(1.+exp(-r));
}
if (i_activation == 1)
{
//tanh
r=s1[j];
x11[j]=tanh(r);
}
}//j

if(ill==0)
{
	for(j=0;j<l1;j++)
	{
	x4[j]=x11[j];
	}
}


//for the third layer
for(j=0;j<l3;j++)
{
  s3[j]=0.;
    for(i=0;i<l1;i++)
    {
    s3[j]=s3[j]+w3[j][i]*x11[i];
    }
    x3[j]=s3[j];// output
	fprintf(stream3, "\n %f",x3[j]);
}//j


}//jj

}//if
//***************** END OF TRAINING ***************************

iter4:

fclose(stream1);  /*resulted RMSE for the test pool*/
fclose(stream2);  /*resulted eps prediction for the test and learning pools*/
fclose(stream3);  /*resulted RMSE for the learning pool*/

getch();
getch();
return(0);


}