//test break
int main(){
    int i;
    i = 0;int sum;sum = 0;
    while(i < 100){
        if(i % 20 == 0)
        {
            break;
        }
        // do something
        sum= sum + i;
        i = i+ 1;   
    }
    return sum+sum;
}