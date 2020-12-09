# include <iostream>
# include <string>
# include <map>
# include <cctype>

using namespace std;


map<string,double> table;

/////////////////////////////////////////////
int no_of_errors;
double error(const string& s){

    no_of_errors++;
    cerr<<"error:"<<s<<'\n';

    return 1;

}
////////////////////////////////////

enum class Kind:char {

    name,number,end,
    plus='+',minus='-',mul='*',div='/',print=';',assign='=',lp='(',rp=')'

};

struct Token{

    Kind kind;
    string string_value;
    double number_value;
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
                return ct={Kind::print};  
           case '*':
           case '/':
           case '+': 
           case '-':
           case '(':
           case ')':
           case '=':
                return ct={static_cast<Kind> (ch)};
           case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': 
           case '.':  
                ip->putback(ch);
                *ip>>ct.number_value;
                ct.kind=Kind::number;
                return ct;
            default:
                if(isalpha(ch)){
                 ct.string_value=ch;  
                //  ip->putback(ch);
                //  *ip>>ct.string_value;
                while(ip->get(ch) && isalnum(ch))
                      ct.string_value+=ch;
                //  ct.kind=Kind::name;
                 return ct={Kind::name};   

                }

          error("bad token");
          return ct={Kind::print};

    }
}

////////////////////////////

Token_stream ts{cin};

void calculate(){
    

}


//////////////////////////////////////////////

int main(){

        table["pi"] =3.1415926;
        table["e"]=2.71818;

        calculate();


        return  no_of_errors;

}
