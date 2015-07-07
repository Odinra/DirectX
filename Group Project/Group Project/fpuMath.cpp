#include "fpuMath.h"

/***********************************************************************
	fpuAdd used to add two real numbers together(doubles in this case)
	requires two doubles be passed to it, inline function
	returns a double data type, and can be used as a parameter for
	another function that requires the double data type
***********************************************************************/
double fpuAdd(const double dAddNumOne, const double dAddNumTwo)
{
	double dAddResult = 0;
	//Load the 1st number passed, add 2nd number to first, store result
	_asm
	{
		FLD dAddNumOne
		FADD dAddNumTwo
		FSTP dAddResult
	}
	return dAddResult;
}

/***********************************************************************
	fpuSub used to subtract two real numbers together(doubles in this case)
	requires two doubles be passed to it, inline function
	returns a double data type, and can be used as a parameter for
	another function that requires the double data type
***********************************************************************/
double fpuSub(const double dSubNumOne, const double dSubNumTwo)
{
	double dSubResult = 0;
	//Load the 1st number passed, sub 2nd number to first, store result
	_asm
	{
		FLD dSubNumOne
		FSUB dSubNumTwo
		FSTP dSubResult
	}
	return dSubResult;
}

/***********************************************************************
	fpuDiv used to divide two real numbers together(doubles in this case)
	requires two doubles be passed to it, inline function
	returns a double data type, and can be used as a parameter for
	another function that requires the double data type
***********************************************************************/
double fpuDiv(const double dDivNumOne, const double dDivNumTwo)
{
	double dDivResult = 0;
	//Load the 1st number passed, Div 1st number by 2nd, store result
	_asm
	{
		FLD dDivNumOne
		FDIV dDivNumTwo
		FSTP dDivResult
	}
	return dDivResult;
}

/***********************************************************************
	fpuMul used to multiply two real numbers together(doubles in this case)
	requires two doubles be passed to it, inline function
	returns a double data type, and can be used as a parameter for
	another function that requires the double data type
***********************************************************************/
double fpuMul(const double dMulNumOne, const double dMulNumTwo)
{
	double dMulResult = 0;
	//Load the 1st number passed, add 2nd number to first, store result
	_asm
	{
		FLD dMulNumOne
		FMUL dMulNumTwo
		FSTP dMulResult
	}
	return dMulResult;
}



/***********************************************************************
		fpuModulus used to find the remainder of a real number(double)
		requires two numerical values be passed to it, inline function
		returns a double data type, and can be used as a parameter for
		another function that requires the double data type
	***********************************************************************/
double fpuModulus(const double dDivide, const double dDivideBy)
{
	double dResult = 0;
	//Load the 1st number passed, add 2nd number to first, store result
	_asm
	{
		FLD dDivideBy
		FLD dDivide
		FPREM 
		FSTP dResult
	}
	return dResult;
}

double fpuSqRoot(const double dNum)
{
	double D, N, x0, num2or6, temp, temp2 = 1;

	if(dNum <10)
		D = 1;
	else if (dNum < 100)
		D = 2;
	else if (dNum < 1000)
		D =3;
	else if (dNum < 10000)
		D =4;
	else if (dNum < 100000)
		D =5;
	else if (dNum < 1000000)
		D =6;
	else if (dNum < 10000000)
		D =7;
	else if (dNum < 100000000)
		D =8;
	else if (dNum < 1000000000)
		D =9;
	else D = 10;

	//n=(D-2)/2
	N = fpuDiv(fpuSub(D, 2),2);

	if(fpuModulus(D, 2) == 0)
		num2or6 = 6;
	else num2or6 = 2;

	for(int i = 0; i < N;i = fpuAdd(i, 1))
	{
		temp2 = fpuMul(temp2, 10);
	}

	x0 = fpuMul(temp2, num2or6);
	temp = x0;

	for (int i = 0; i < fpuAdd(D, 1);i = fpuAdd(i, 1))
	{
		temp = fpuMul(.5, fpuAdd(temp, fpuDiv(dNum, temp)));
	}

	return temp;

}

/***********************************************************************
	matrix3x3Add used to add two 3x3 matrices together
	requires eightteen doubles be passed to it
***********************************************************************/
void matrix3x3Add(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, 
	const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
	const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
	const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
	const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,  
	const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3)
{
 double dResult[3][3];
 dResult[0][0] = fpuAdd(dMat1R1C1, dMat2R1C1);

 dResult[0][1] = fpuAdd(dMat1R1C2, dMat2R1C2);

 dResult[0][2] = fpuAdd(dMat1R1C3, dMat2R1C3);

 

 dResult[1][0] = fpuAdd(dMat1R2C1, dMat2R2C1);

 dResult[1][1] = fpuAdd(dMat1R2C2, dMat2R2C2);

 dResult[1][2] = fpuAdd(dMat1R2C3, dMat2R2C3);

 

 dResult[2][0] = fpuAdd(dMat1R3C1, dMat2R3C1);

 dResult[2][1] = fpuAdd(dMat1R3C2, dMat2R3C2);

 dResult[2][2] = fpuAdd(dMat1R3C3, dMat2R3C3);

}
  
	/***********************************************************************
		matrix2x2Add used to add two 2x2 matrices together
		requires eight doubles be passed to it
	***********************************************************************/
	void matrix2x2Add(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2)
{
 double dResult[2][2];
 dResult[0][0] = fpuAdd(dMat1R1C1, dMat2R1C1);

 dResult[0][1] = fpuAdd(dMat1R1C2, dMat2R1C2);

 

 dResult[1][0] = fpuAdd(dMat1R2C1, dMat2R2C1);

 dResult[1][1] = fpuAdd(dMat1R2C2, dMat2R2C2);

}	
	
	/***********************************************************************
		matrix4x4Add used to add two 4x4 matrices together
		requires thrity-two doubles be passed to it
	***********************************************************************/
	void matrix4x4Add(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, const double dMat1R1C4,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, const double dMat1R2C4,
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, const double dMat1R3C4,
					  const double dMat1R4C1, const double dMat1R4C2, const double dMat1R4C3, const double dMat1R4C4,
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, const double dMat2R1C4,
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3, const double dMat2R2C4,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3, const double dMat2R3C4,
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4)
{
 double dResult[4][4];
 dResult[0][0] = fpuAdd(dMat1R1C1, dMat2R1C1);

 dResult[0][1] = fpuAdd(dMat1R1C2, dMat2R1C2);

 dResult[0][2] = fpuAdd(dMat1R1C3, dMat2R1C3);

 dResult[0][3] = fpuAdd(dMat1R1C4, dMat2R1C4);

 

 dResult[1][0] = fpuAdd(dMat1R2C1, dMat2R2C1);

 dResult[1][1] = fpuAdd(dMat1R2C2, dMat2R2C2);

 dResult[1][2] = fpuAdd(dMat1R2C3, dMat2R2C3);

 dResult[1][3] = fpuAdd(dMat1R2C4, dMat2R2C4);

 

 dResult[2][0] = fpuAdd(dMat1R3C1, dMat2R3C1);

 dResult[2][1] = fpuAdd(dMat1R3C2, dMat2R3C2);

 dResult[2][2] = fpuAdd(dMat1R3C3, dMat2R3C3);

 dResult[2][3] = fpuAdd(dMat1R3C4, dMat2R3C4);


 
 dResult[3][0] = fpuAdd(dMat1R4C1, dMat2R4C1);

 dResult[3][1] = fpuAdd(dMat1R4C2, dMat2R4C2);

 dResult[3][2] = fpuAdd(dMat1R4C3, dMat2R4C3);

 dResult[3][3] = fpuAdd(dMat1R4C4, dMat2R4C4);
}
/***********************************************************************
	matrix3x3Sub used to Subtract two 3x3 matrices
	requires eightteen doubles be passed to it
***********************************************************************/
void matrix3x3Sub(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, 
	const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
	const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
	const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
	const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,  
	const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3)
{
 double dResult[3][3];
 dResult[0][0] = fpuSub(dMat1R1C1, dMat2R1C1);

 dResult[0][1] = fpuSub(dMat1R1C2, dMat2R1C2);

 dResult[0][2] = fpuSub(dMat1R1C3, dMat2R1C3);

 

 dResult[1][0] = fpuSub(dMat1R2C1, dMat2R2C1);

 dResult[1][1] = fpuSub(dMat1R2C2, dMat2R2C2);

 dResult[1][2] = fpuSub(dMat1R2C3, dMat2R2C3);

 

 dResult[2][0] = fpuSub(dMat1R3C1, dMat2R3C1);

 dResult[2][1] = fpuSub(dMat1R3C2, dMat2R3C2);

 dResult[2][2] = fpuSub(dMat1R3C3, dMat2R3C3);

}
	
/***********************************************************************
	matrix4x4Sub used to Subtract two 4x4 matrices
	requires thirty-two doubles be passed to it
***********************************************************************/
void matrix4x4Sub(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, const double dMat1R1C4,
					const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, const double dMat1R2C4,
					const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, const double dMat1R3C4,
					const double dMat1R4C1, const double dMat1R4C2, const double dMat1R4C3, const double dMat1R4C4,
					const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, const double dMat2R1C4,
					const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3, const double dMat2R2C4,
					const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3, const double dMat2R3C4,
					const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4)
{
 double dResult[4][4];
 dResult[0][0] = fpuSub(dMat1R1C1, dMat2R1C1);

 dResult[0][1] = fpuSub(dMat1R1C2, dMat2R1C2);

 dResult[0][2] = fpuSub(dMat1R1C3, dMat2R1C3);

 dResult[0][3] = fpuSub(dMat1R1C4, dMat2R1C4);

 

 dResult[1][0] = fpuSub(dMat1R2C1, dMat2R2C1);

 dResult[1][1] = fpuSub(dMat1R2C2, dMat2R2C2);

 dResult[1][2] = fpuSub(dMat1R2C3, dMat2R2C3);

 dResult[1][3] = fpuSub(dMat1R2C4, dMat2R2C4);

 

 dResult[2][0] = fpuSub(dMat1R3C1, dMat2R3C1);

 dResult[2][1] = fpuSub(dMat1R3C2, dMat2R3C2);

 dResult[2][2] = fpuSub(dMat1R3C3, dMat2R3C3);

 dResult[2][3] = fpuSub(dMat1R3C4, dMat2R3C4);



 dResult[3][0] = fpuSub(dMat1R4C1, dMat2R4C1);

 dResult[3][1] = fpuSub(dMat1R4C2, dMat2R4C2);

 dResult[3][2] = fpuSub(dMat1R4C3, dMat2R4C3);

 dResult[3][3] = fpuSub(dMat1R4C4, dMat2R4C4);

}	

	/***********************************************************************
		matrix2x2Sub used to Subtract two 2x2 matrices
		requires eight doubles be passed to it
	***********************************************************************/

	void matrix2x2Sub(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2)
{
 double dResult[2][2];
 dResult[0][0] = fpuSub(dMat1R1C1, dMat2R1C1);

 dResult[0][1] = fpuSub(dMat1R1C2, dMat2R1C2);


 dResult[1][0] = fpuSub(dMat1R2C1, dMat2R2C1);

 dResult[1][1] = fpuSub(dMat1R2C2, dMat2R2C2);

}


/***********************************************************************
	matrix3x3Mul used to multiply two 3x3 matrices together
	requires eightteen doubles be passed to it
***********************************************************************/



void matrix3x3Mul(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3,
  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3,
  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3,
   const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3)
{

 double tempResult[5];
 double dResult[3][3];

 

 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C1);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[0][0] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C2);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[0][1] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C3);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[0][2] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C1);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[1][0] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C2);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[1][1] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C3);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[1][2] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C1);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[2][0] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C2);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[2][1] = fpuAdd(tempResult[2], tempResult[3]);

 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C3);

 tempResult[3] = fpuAdd(tempResult[0], tempResult[1]);

 dResult[2][2] = fpuAdd(tempResult[2], tempResult[3]);

}



	/***********************************************************************
		matrix2x2Mul used to multiply two 2x2 matrices together
		requires eight doubles be passed to it
	***********************************************************************/	
	void matrix2x2Mul(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2)
{

 double tempResult[5];
 double dResult[2][2];

 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C1);

 dResult[0][0] = fpuAdd(tempResult[0], tempResult[1]);


 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C2);

 dResult[0][1] = fpuAdd(tempResult[0], tempResult[1]);


 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C1);

 dResult[1][0] = fpuAdd(tempResult[0], tempResult[1]);


 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C2);

  dResult[1][1] = fpuAdd(tempResult[0], tempResult[1]);

}


	
	/***********************************************************************
		matrix4x4Mul used to multiply two 4x4 matrices together
		requires thirty-two doubles be passed to it
	***********************************************************************/
	void matrix4x4Mul(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3, const double dMat1R1C4,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, const double dMat1R2C4,
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, const double dMat1R3C4,
					  const double dMat1R4C1, const double dMat1R4C2, const double dMat1R4C3, const double dMat1R4C4,
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, const double dMat2R1C4,
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3, const double dMat2R2C4,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3, const double dMat2R3C4,
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4)
	
{
 double tempResult[6];
 double dResult[4][4];
 

 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C1);

 tempResult[3] = fpuMul(dMat1R1C4, dMat2R4C1);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[0][0] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C2);

 tempResult[3] = fpuMul(dMat1R1C4, dMat2R4C2);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[0][1] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C3);

 tempResult[3] = fpuMul(dMat1R1C4, dMat2R4C3);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[0][2] = fpuAdd(tempResult[4], tempResult[5]);


 
 tempResult[0] = fpuMul(dMat1R1C1, dMat2R1C4);

 tempResult[1] = fpuMul(dMat1R1C2, dMat2R2C4);

 tempResult[2] = fpuMul(dMat1R1C3, dMat2R3C4);

 tempResult[3] = fpuMul(dMat1R1C4, dMat2R4C4);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[0][3] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C1);

 tempResult[3] = fpuMul(dMat1R2C4, dMat2R4C1);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[1][0] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C2);

 tempResult[3] = fpuMul(dMat1R2C4, dMat2R4C2);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[1][1] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C3);

 tempResult[3] = fpuMul(dMat1R2C4, dMat2R4C3);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[1][2] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R2C1, dMat2R1C4);

 tempResult[1] = fpuMul(dMat1R2C2, dMat2R2C4);

 tempResult[2] = fpuMul(dMat1R2C3, dMat2R3C4);

 tempResult[3] = fpuMul(dMat1R2C4, dMat2R4C4);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[1][3] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C1);

 tempResult[3] = fpuMul(dMat1R3C4, dMat2R4C1);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[2][0] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C2);

 tempResult[3] = fpuMul(dMat1R3C4, dMat2R4C2);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[2][1] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C3);

 tempResult[3] = fpuMul(dMat1R3C4, dMat2R4C3);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[2][2] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R3C1, dMat2R1C4);

 tempResult[1] = fpuMul(dMat1R3C2, dMat2R2C4);

 tempResult[2] = fpuMul(dMat1R3C3, dMat2R3C4);

 tempResult[3] = fpuMul(dMat1R3C4, dMat2R4C4);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[2][3] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R4C1, dMat2R1C1);

 tempResult[1] = fpuMul(dMat1R4C2, dMat2R2C1);

 tempResult[2] = fpuMul(dMat1R4C3, dMat2R3C1);

 tempResult[3] = fpuMul(dMat1R4C4, dMat2R4C1);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[3][0] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R4C1, dMat2R1C2);

 tempResult[1] = fpuMul(dMat1R4C2, dMat2R2C2);

 tempResult[2] = fpuMul(dMat1R4C3, dMat2R3C2);

 tempResult[3] = fpuMul(dMat1R4C4, dMat2R4C2);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[3][1] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R4C1, dMat2R1C3);

 tempResult[1] = fpuMul(dMat1R4C2, dMat2R2C3);

 tempResult[2] = fpuMul(dMat1R4C3, dMat2R3C3);

 tempResult[3] = fpuMul(dMat1R4C4, dMat2R4C3);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[3][2] = fpuAdd(tempResult[4], tempResult[5]);



 tempResult[0] = fpuMul(dMat1R4C1, dMat2R1C4);

 tempResult[1] = fpuMul(dMat1R4C2, dMat2R2C4);

 tempResult[2] = fpuMul(dMat1R4C3, dMat2R3C4);

 tempResult[3] = fpuMul(dMat1R4C4, dMat2R4C4);

 tempResult[4] = fpuAdd(tempResult[0], tempResult[1]);

 tempResult[5] = fpuAdd(tempResult[2], tempResult[3]);

 dResult[3][3] = fpuAdd(tempResult[4], tempResult[5]);



}