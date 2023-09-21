int MaxSubseqSum2( int List[], int N )
{
	int i, j;
	int ThisSum, MaxSum = 0;

	for( i=0; i<N; i++ ) {     
		ThisSum = 0; 
		for( j=i; j<N; j++ ) {
			ThisSum += List[j];
			if( ThisSum > MaxSum ) 
				MaxSum = ThisSum;   
		} 
    }
	return MaxSum;
}
