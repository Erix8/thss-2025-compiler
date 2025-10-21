const int a=1; int b= 2;
int arr[10]={1,2,3};

int plus(int x, int y) 
{
return x + y;
}

void print() {}

int main() 
{
  int c;
  {
    int  cond=1;
    if (cond == 1) 
    {
        c=a+b;
    } 
    else if (cond==2) 
    {
        c=a-b;
    }
    else c=a*b;
  }
  print();   return 0;
}