#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
 
long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i,a = 0,pub_key,prv_key;
char msg[100];
int prime(long int);
void choose_e();
long int choose_d(long int);
void encrypt();
void decrypt();
 
int main() {

            int choice, index;
            char ch;

            printf("\n!!WELCOME TO THE PROGRAM!!\n");
  
            printf("\nENTER YOUR MESSAGE: ");
            fflush(stdin);
            fgets(msg, sizeof(msg), stdin);

            for(i=0;msg[i]!='\0';i++){
               m[i]=msg[i];
            }

    do{  
            printf("\nPress 1 to Generate new PRIVATE KEY and PUBLIC KEY");
            printf("\nPress 2 to Encrypt the Message");
            printf("\nPress 3 to Decrypt the Message");
            printf("\nPress 4 to Enter a new message");      
            printf("\nEnter your choice: ");

            scanf("%d", &choice);

        switch(choice){

            case 1 :
                        printf("\nENTER FIRST PRIME NUMBER: ");
                        scanf("%ld",&p);
                        flag=prime(p);
                        if(flag==0) {
                                    printf("\nWRONG INPUT\n");
                                    //getch();
                                    exit(1);
                        }
             
                        printf("\n\nENTER ANOTHER PRIME NUMBER: ");
                        scanf("%ld",&q);
                        flag=prime(q);
                        if(flag==0||p==q) {
                                    printf("\nWRONG INPUT\n");
                                //  getch();
                                    exit(1);
                        }

                        n=p*q;
                        t=(p-1)*(q-1);
                        choose_e();
                        printf("\nPOSSIBLE VALUES OF 'PUBLIC KEY' AND 'PRIVATE KEY' ARE:\n\n");
                        printf("PUBLIC KEY\t\tPRIVATE KEY\n");
                        for (i=0;i<j-1;i++)
                        printf("\n%ld\t\t\t%ld",e[i],d[i]);

                        index = (rand() % (j-1) - 0) + 0;

                        pub_key = e[index];
                        prv_key = d[index];

                        printf("\nTHE PUBLIC KEY & PRIVATE KEY FOR THIS PARTICULAR RUN ARE: ");
                        printf("%ld and %ld", pub_key,prv_key);

                        break;


            case 2 :    encrypt();
                        a = 1;
                        break;

            case 3 :    if(a!=0)
                        decrypt();

                        else{
                            printf("\n!!!PLEASE GENERATE THE KEYS FIRST!!!\n");
                        }

                        break;

            case 4 :    printf("\nENTER YOUR MESSAGE: ");
                        fflush(stdin);
                        fgets(msg, sizeof(msg), stdin);

                        for(i=0;msg[i]!='\0';i++){
                            m[i]=msg[i];
                        }   

                        break; 

            default : printf("\nPLEASE ENTER A VALID CHOICE!!");
                      break;                   
        }

        printf("\nDO YOU WANT TO CONTINUE?? (Y/N): ");
        fflush(stdin);
        scanf("%c", &ch);

    }while(ch == 'Y' || ch == 'y'); 

    printf("\nEXITING THE PROGRAM, THANKS FOR USING!!\n...");  

    return 0;        
}

int prime(long int pr) {
            int i;
            j=sqrt(pr);
            for (i=2;i<=j;i++) {
                        if(pr%i==0)
                            return 0;
            }
            return 1;
}
void choose_e() {
            int k;
            k=0;
            for (i=2;i<t;i++) {
                        if(t%i==0)
                            continue;
                        flag=prime(i);
                        if(flag==1&&i!=p&&i!=q) {
                                    e[k]=i;
                                    flag=choose_d(e[k]);
                                    if(flag>0) {
                                                d[k]=flag;
                                                k++;
                                    }
                                    if(k==99)
                                            break;
                        }
            } 
}
long int choose_d(long int x) {
            long int k=1;
            while(1) {
                        k=k+t;
                        if(k%x==0)
                            return(k/x);
            }
}
void encrypt() {
            long int pt,ct,key=pub_key,k,len;
            i=0;
            len=strlen(msg);
            while(i!=len) {
                        pt=m[i];
                        if(pt ==' '){
                            en[i] = '`';
                            i++;
                        }
                        
                        else if(pt =='\n'){
                            en[i] = '~';
                            i++;
                        }

                        else{
                            pt=pt-96;
                            k=1;
                            for (j=0;j<key;j++) {
                                    k=k*pt;
                                    k=k%n;
                            }
                            temp[i]=k;
                            ct=k+96;
                            en[i]=ct;
                            i++;
                        }
                        
            }
            en[i]=-1;
            printf("\nTHE ENCRYPTED MESSAGE IS\n");
            for (i=0;en[i]!=-1;i++)
            printf("%c",en[i]);
}
void decrypt() {
            long int pt,ct,key=prv_key,k;
            i=0;
            while(en[i]!=-1) {

                        ct=temp[i];

                        if(ct == '`'){
                            m[i] = " ";
                            i++;
                        }

                        else if(ct == '~'){
                            m[i] = "\n";
                            i++;
                        }

                        else{
                            
                            k=1;
                            for (j=0;j<key;j++) {
                                        k=k*ct;
                                        k=k%n;
                            }
                            pt=k+96;
                            m[i] = pt;
                            i++;
                        }
                        
            }
            m[i]=-1;
            printf("\nTHE DECRYPTED MESSAGE IS\n");
            for (i=0;m[i]!=-1;i++)
                if(m[i] == '`'){
                    printf(" ");
                }
                else{
            printf("%c",m[i]);
        }
}
