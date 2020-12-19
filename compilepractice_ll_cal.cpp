# include <iostream>
# include <string>
# include <map>
# include <cctype>
# include <math.h>
//# include <compilepractise>

using namespace std;

typedef double (*MATHFUN) (double );

map<string,double> table;

map<string,MATHFUN> mathfun_table;

/////////////////////////////////////////////
int no_of_errors;
double error(const string& s){

    no_of_errors++;
    cerr<<"error:"<<s<<'\n';

    return 1;

}
////////////////////////////////////



enum class Kind:char {

    name,number,end='#',func,
    plus='+',minus='-',mul='*',div='/',print=';',assign='=',lp='(',rp=')'

};

struct Token{

    Kind kind;
    string string_value;
    double number_value;
    MATHFUN nowfun;
};

/////////////////////////////////////

class Token_stream{
    public:
          Token_stream(istream& s ): ip{&s},owns{false}{}
          Token_stream(istream* p ): ip{p},  owns{true}{}
          Token_stream(){close();}

          Token get();
          Token& current();

          void set_input(istream& s){close();ip=&s;owns=false;}
          void set_input(istream* p){close();ip=p;owns=true;}


    private:
          void close(){if (owns) delete ip;}
          istream* ip; 
          bool owns;
          Token ct={Kind::end};
    
};

Token Token_stream::get(){

    char ch=0;
    //*ip>>ch;

    do{
      if(!ip->get(ch)) return ct={Kind::end};
    }while(ch!='\n' && isspace(ch));

    switch (ch) {
           case  0:
                return ct={Kind::end};
           
           case ';': 
           case '\n':
                cout<<ch;
                return ct={Kind::print};  
           case '#':     
           case '*':
           case '/':
           case '+': 
           case '-':
           case '(':
           case ')':
           case '=':
                cout<<ch;
                return ct={static_cast<Kind> (ch)};
           case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': 
           case '.':  
                ip->putback(ch);
                *ip>>ct.number_value;
                ct.kind=Kind::number;
                cout<<ct.number_value;
                return ct; 
            default:
                if(isalpha(ch)){
                 ct.string_value=ch;  
                
                //  *ip>>ct.string_value;
                while(ip->get(ch) && isalnum(ch))
                      ct.string_value+=ch;
                      cout<<ct.string_value;
                      if (ch=='(')
                      {
                          //ip->putback(ch);
                          MATHFUN tempfun;
                           ct.kind=Kind::func;
                           tempfun=mathfun_table[ct.string_value];
                           if(tempfun==nullptr){
                               error("Not defined function");
                               ct={Kind::print};

                           }
                          ct.nowfun=mathfun_table[ct.string_value];
                           //ct.nowfun=sqrt;
                      } else
                      {
                          ip->putback(ch);
                           ct.kind=Kind::name;
                      }
                      
                       
                

                 return ct;
                //   table[ct.string_value]=0;
                 
                //  return ct={Kind::name};   

                }

          error("bad token");
          return ct={Kind::print};

    }
}

Token& Token_stream::current()
{

    return ct;
}


////////////////////////////

Token_stream ts{cin};

////////////////////////
double expr(bool get);
double prim(bool get){
    if(get) ts.get();

    switch(ts.current().kind){

        case Kind::number:
         {
            double v=ts.current().number_value;
            ts.get();
            return v;

         }
        case Kind::name:
         {

             double& v=table[ts.current().string_value];
             if(ts.get().kind==Kind::assign) v=expr(true);
             return v;
         } 
         
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
         {

           auto e=expr(true);
           if(ts.current().kind!=Kind::rp) return error("')' expected");
           ts.get();
           return e;

         } 

         case Kind::func:
         {
             double& v=table[ts.current().string_value];
             v=ts.current().nowfun( expr(true));
             if(ts.current().kind!=Kind::rp) return error("')' expected");
             ts.get();
             return v;

         } 

         default:

          return error("primary expected");   

    }

}

double term(bool get){

      double left=prim(get);

      for(;;){

          switch(ts.current().kind){
              case Kind::mul:
                left*=prim(true);
                break;
              case Kind::div:
                 if(auto d=prim(true)){
                 left /=d; 
                 break;
                 } 
                error("devide by 0"); 
              default:
                 return left;  


          }
      }

}

double expr(bool get){

      double left=term(get);

      for(;;){

          switch(ts.current().kind){
              case Kind::plus:

                 left+=term(true);
                 break;
              case Kind::minus:

                 left-=term(true);
                 break;

               default:
                  return left;



          }
      }


}
void B();
void A();

void D1(){
    
     switch(ts.current().kind){
             
            case Kind::print:
            case Kind::rp:
            case Kind::plus:
            case Kind::minus:
            case Kind::mul:
            case Kind::div:
            {
              break;

            }
            
            
           
            case Kind::assign:
            {
                ts.get();
                B();
                break;
               
            } 

            default:
               error("invalid input d1");
        
        } 
}

void D(){
   
     switch(ts.current().kind){
             
            
            
            case Kind::number:
                 ts.get(); 
                 break;
            case Kind::name:
            {
                ts.get();
                D1();
                break;
            }
            case Kind::lp:
            {
                ts.get();
                B();
                ts.get();
                break;
            }
            case Kind::minus:
            {
                

                ts.get();
                D();
                break;
            } 

            default:
               error("invalid input d");
        
        }  
}
void C1(){
    
     switch(ts.current().kind){
             
            case Kind::print:
            case Kind::rp:
            case Kind::plus:
            case Kind::minus:
            {
            break;

            }
            
            
            case Kind::mul :
            case Kind::div:
            {
                ts.get();
                D();

                
                C1();
                break;
            } 

            default:
               error("invalid input c1");
        
        }  
}
void C(){

     
     switch(ts.current().kind){
             
            
            
            case Kind::number:
            case Kind::name:
            case Kind::lp:
            case Kind::minus:
            {
               
                D();

               
                C1();
                break;
            } 

            default:
               error("invalid input c");
        
        }   
}
void B1(){
    
     switch(ts.current().kind){
             
            case Kind::print:
            case Kind::rp:
            {
            break;

            }
            
            
            case Kind::plus:
            case Kind::minus:
            {
                ts.get();
                C();

                
                B1();
                break;
            } 

            default:
               error("invalid input b1");
        
        }        

}
void B(){
    
     switch(ts.current().kind){
             
            
            
            case Kind::number:
            case Kind::name:
            case Kind::lp:
            case Kind::minus:
            {
                
                C();

               
                B1();
                break;
            } 

            default:
               error("invalid input b");
        
        }        
     
}
void A1(){

    
     switch(ts.current().kind){
            
            case Kind::end:
            {
            break;

            }
            
            case Kind::number:
            case Kind::name:
            case Kind::lp:
            case Kind::minus:
            {
              
                A();
                break;
            } 

            default:
              if(ts.current().kind!=Kind::end && ts.current().kind!=Kind::print) error("invalid input a1");
        
        }
}

void A(){
     
     
     switch(ts.current().kind){
             
            
            
            case Kind::number:
            case Kind::name:
            case Kind::lp:
            case Kind::minus:
            {
               
                B();

              //b 
                if(ts.current().kind!=Kind::print)  error("print expect a");
                ts.get();
               
                A1();
                
                

                break;
            } 

            default:
               if(ts.current().kind!=Kind::end)  error("invalid input a");
        
        }



}
///////////////////////////////////////

void P()
{
    
      for(;;)
      {
          ts.get();
          

           switch(ts.current().kind)
           {
               
                
                case Kind::number:
                case Kind::name:
                case Kind::lp:
                case Kind::minus:
                {
                    
                    A();

                    
                
                    break;

                } 

                default:
                break;
           }
        cout<<"from P end"<<'\n';
           if(ts.current().kind==Kind::end) break;
           if(ts.current().kind==Kind::print) continue;
             
        }


     
      
       

        



}
//////////////////////////////////////////////

int main(){

        table["pi"] =3.1415926535897932385;
        table["e"]=2.7182818284590452354;

        //Functions in cmath(math.h)    
        mathfun_table["sqrt"]=sqrt;
        mathfun_table["log10"]=log10;
        mathfun_table["exp"]=exp;
        mathfun_table["sin"]=sin;
        mathfun_table["fabs"]=fabs;
        mathfun_table["tan"]=tan;

        //Token now_token =  ts.get();
        P();


        return  no_of_errors;

}
