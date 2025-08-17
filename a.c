#include<stdio.h>
#include<string.h>

int main()
{
   int n,i,j,a[10],t;
   scanf("%d",&n);
   //dsfgdg /*jhdfsghi */
   /*hsgduagd //dfsigdfg*/
   for(i=0;i<n;i++)
   scanf("%d",&a[i]);
   //this is a comment
   for(i=0;i<n-1;i++)
   {
    for(j=0;j<n-1;j++)
    {
        if(a[j]>a[j+1])
        {
            t=a[j];
            a[j]=a[j+1];
            a[j+1]=t;
        }
    }
   }
  /* get_file_type*/
   for(i=0;i<n;i++)
   printf("%d",a[i]);

}