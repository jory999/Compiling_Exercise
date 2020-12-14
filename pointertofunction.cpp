# include <iostream>
# include <vector>
# include <cstring> 
# include <string.h>
#include <string>
# include <algorithm>

using namespace std;

/* #ifndef __HAVE_ARCH_STRCMP
 /**
  * strcmp - Compare two strings
  * @cs: One string
  * @ct: Another string
  */
 /*#undef strcmp
 int strcmp(const char *cs, const char *ct)
 {
         unsigned char c1, c2;
 
         while (1) {
                 c1 = *cs++;
                 c2 = *ct++;
                 if (c1 != c2)
                         return c1 < c2 ? -1 : 1;
                 if (!c1)
                         break;
         }
         return 0;
 }
//  EXPORT_SYMBOL(strcmp);
 #endif */



typedef int  (*CFT)(const void*,const void*) ;

using CTT=int(const void*,const void*);


void ssort(void* base, size_t n,size_t sz,CTT cmp){

     for(int gap=n/2;0<gap;gap/=2){
         for(int i=gap;i!=n;i++){
             for(int j=i-gap;0<=j;j-=gap){

                 char* b=static_cast<char*>(base);
                 char* pj=b+j*sz;
                 char* pjg=b+(j+gap)*sz;

                 if(cmp(pjg,pj)<0){
                   for(int k=0;k!=sz;k++){
                       char temp=pj[k];
                       pj[k]=pjg[k];
                       pjg[k]=temp;
                   }

                 }




             }
         }
     }

}

struct User{

    const char* name;
    const char* dept;
    int id;    
};



/* vector<User>  heads = {
    "Ritchie D.M.",   "dmr",  11271,
    "Sethi R.",       "ravi", 11272,
    "Szymanski T.G.", "tgs",  11273,
    "Schr yer N.L.",  "nls",  11274,
    "Schr yer N.L.",  "nls",  11275,
    "Kernighan B.W.", "bwk",  11276
    }; */

void print_id(vector<User>& v){

    for(auto& x:v){
        cout<<x.name<<'\t'<<x.id<<'\t'<<x.dept<<'\n';
    }
}

int cmp1(const void* p,const void* q){

     return strcmp(static_cast<const User*>(p)->name,static_cast<const User*>(q)->name );
     }
int cmp2(const void* p,const void* q){

     return static_cast<const User*>(p)->id - static_cast<const User*>(q)->id;
}     

vector<User>  heads ;

int main(){

     
     User u;
     u={"Ritchie D.M.",   "dmr",  11271};
     heads.push_back(u);

     u={"Sethi R.",       "ravi", 11272};
     heads.push_back(u);

     u={"Szymanski T.G.", "tgs",  11273};
     heads.push_back(u);

     u={"Schr yer N.L.",  "nls",  11274};
     heads.push_back(u);

     u={"Schr yer N.L.",  "nls",  11275};
     heads.push_back(u);

     u={"Kernighan B.W.", "bwk",  11276};
     heads.push_back(u);

    print_id(heads);
    cout << '\n';
     
    /*  = {
    "Ritchie D.M.",   "dmr",  11271,
    "Sethi R.",       "ravi", 11272,
    "Szymanski T.G.", "tgs",  11273,
    "Schr yer N.L.",  "nls",  11274,
    "Schr yer N.L.",  "nls",  11275,
    "Kernighan B.W.", "bwk",  11276
    }; */

     ssort(&heads,6,sizeof(User),cmp1);
     print_id(heads);
      cout << '\n';

     /* ssort(&heads,6,sizeof(User),cmp2);
      print_id(heads);
      cout << '\n'; */

      cout << "Heads in alphabetical order:\n";
sort(heads.begin(), heads.end(),[](const User& x, const User& y) { return x.name>=y.name; });
print_id(heads);
cout << '\n';
cout << "Heads in order of department number:\n";
sort(heads.begin(), heads.end(),[](const User& x, const User& y) { return x.dept>y.dept; });
print_id(heads);

}