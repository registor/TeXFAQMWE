int partizione(int a[], int i, int j)
{
	int temp;
	int x;

	x=a[(i+j)/2];
	while ((i<j)&&(a[i]<=x)) i++;
	while(a[j]>x) j--;
	while(i<j)
		   {
			   temp=a[i]; a[i]=a[j]; a[j]=temp;
			   i++; j--;
			   while (a[i]<=x) i++;
			   while (a[j]>x) j--;
		   }
		   return j;
}

void quicksort_ric (int a[], int l, int r)
{
	int m;
	m=partizione(a, l, r);
	if (l<r)
 {
	if ((m-l+1)<(r-m))
	{
		quicksort_ric (a, l, m);
		quicksort_ric (a, m+1, r);
	}

	else {
		quicksort_ric (a, m+1, r);
		quicksort_ric (a, l, m);
	}

 }
}
