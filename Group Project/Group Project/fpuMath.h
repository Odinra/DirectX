// Floating Point Unit Math Header File
// This contains a list of function prototypes for floating point unit calculations using assembly code combined with C++ in order
// to do math and physics calculations in a low-level language in order to reduce overhead, speed up gameplay, and increase accuracy of
// of calculations by doing the math and physics calculations seperately on the FPU as opposed to the integer unit.

#ifndef FPUMATH_H_
#define FPUMATH_H_

/************************************************************************************************
						Function prototypes
************************************************************************************************/
	/***********************************************************************
		fpuAdd used to add two real numbers together(doubles in this case)
		requires two doubles be passed to it, inline function
		returns a double data type, and can be used as a parameter for
		another function that requires the double data type
	***********************************************************************/
double fpuAdd(const double dAddNumOne, const double dAddNumTwo);

	/***********************************************************************
		fpuSub used to subtract two real numbers together(doubles in this case)
		requires two doubles be passed to it, inline function
		returns a double data type, and can be used as a parameter for
		another function that requires the double data type
	***********************************************************************/
double fpuSub(const double dSubNumOne, const double dSubNumTwo);	

	/***********************************************************************
		fpuDiv used to divide two real numbers together(doubles in this case)
		requires two doubles be passed to it, inline function
		returns a double data type, and can be used as a parameter for
		another function that requires the double data type
	***********************************************************************/
double fpuDiv(const double dDivNumOne, const double dDivNumTwo);	

	/***********************************************************************
		fpuMul used to multiply two real numbers together(doubles in this case)
		requires two doubles be passed to it, inline function
		returns a double data type, and can be used as a parameter for
		another function that requires the double data type
	***********************************************************************/
double fpuMul(const double dMulNumOne, const double dMulNumTwo);	

	

	
	/***********************************************************************
		fpuModulus used to find the remainder of a real number(double)
		requires two numerical values be passed to it, inline function
		returns a double data type, and can be used as a parameter for
		another function that requires the double data type
	***********************************************************************/
double fpuModulus(const double dDivide, const double dDivideBy);	

	/***********************************************************************
		fpuSqroot does rooty-sqaurey things
	***********************************************************************/
double fpuSqRoot(const double dNum);


	/***********************************************************************
		matrix2x2Add used to add two 2x2 matrices together
		requires eight doubles be passed to it
	***********************************************************************/
	void matrix2x2Add(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2);
	/***********************************************************************
		matrix2x2Mul used to multiply two 2x2 matrices together
		requires eight doubles be passed to it
	***********************************************************************/	
	void matrix2x2Mul(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2);
	/***********************************************************************
		matrix2x2Sub used to Subtract two 2x2 matrices
		requires eight doubles be passed to it
	***********************************************************************/	
	void matrix2x2Sub(const double dMat1R1C1, const double dMat1R1C2,
					  const double dMat1R2C1, const double dMat1R2C2, 
					  const double dMat2R1C1, const double dMat2R1C2, 
					  const double dMat2R2C1, const double dMat2R2C2);


	/***********************************************************************
		matrix3x3Add used to add two 3x3 matrices together
		requires eightteen doubles be passed to it
	***********************************************************************/
	void matrix3x3Add(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3);

	/***********************************************************************
		matrix3x3Mul used to multiply two 3x3 matrices together
		requires eightteen doubles be passed to it
	***********************************************************************/
	void matrix3x3Mul(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3);

	/***********************************************************************
		matrix3x3Sub used to Subtract two 3x3 matrices
		requires eightteen doubles be passed to it
	***********************************************************************/
	void matrix3x3Sub(const double dMat1R1C1, const double dMat1R1C2, const double dMat1R1C3,
					  const double dMat1R2C1, const double dMat1R2C2, const double dMat1R2C3, 
					  const double dMat1R3C1, const double dMat1R3C2, const double dMat1R3C3, 
					  const double dMat2R1C1, const double dMat2R1C2, const double dMat2R1C3, 
					  const double dMat2R2C1, const double dMat2R2C2, const double dMat2R2C3,
					  const double dMat2R3C1, const double dMat2R3C2, const double dMat2R3C3);

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
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4);
	
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
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4);
	
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
					  const double dMat2R4C1, const double dMat2R4C2, const double dMat2R4C3, const double dMat2R4C4);

#endif
// END OF HEADER