#ifndef _MATRIX_H_
#define _MATRIX_H_
 
namespace MatrSpace
{
    
    class AbstractMatr
    {
    public:
        AbstractMatr() {}
        AbstractMatr(size_t n, size_t m);
        AbstractMatr(const AbstractMatr&Ob):Matrix(Ob.Matrix) {}
        virtual ~AbstractMatr() {}
        void SetSize(size_t n, size_t m);
        inline const size_t GetRow() const {return Matrix.size();}
        inline const size_t GetCol() const {return Matrix.size();}
        void swap(AbstractMatr&);
    protected:
        std::vector<std::vector <int> > Matrix;
    };
 
    //Math Matr. public from AbstractMatr

    class MathMatr:public AbstractMatr
    {
    public:
        MathMatr():AbstractMatr() {}
        MathMatr(size_t n, size_t m):AbstractMatr(n, m) {}
        MathMatr(const AbstractMatr& Ob):AbstractMatr(Ob) {}
        virtual ~MathMatr() {}
        const MathMatr& operator =(const MathMatr&);
        const MathMatr& operator +=(const MathMatr&);
		const MathMatr& operator -=(const MathMatr&);
        const MathMatr operator +(const MathMatr&) const;
		const MathMatr operator -(const MathMatr&) const;
        const MathMatr& operator *=(const MathMatr&);
        const MathMatr operator *(const MathMatr&) const;
        virtual void input(std::istream&) {}
        virtual void output(std::ostream&) const {}
        
        friend std::ostream& operator <<(std::ostream&, const MathMatr& Ob);
        
        friend std::istream& operator >>(std::istream&, MathMatr& Ob);
        void random_fill();
    };
 
    //InOutMatr class. Public from MathMatr

    class IOMatr:public MathMatr
    {
    public:
        IOMatr():MathMatr() {}
        IOMatr(size_t n, size_t m):MathMatr(n, m) {}
        IOMatr(const AbstractMatr& Ob):MathMatr(Ob) {}
        virtual ~IOMatr() {}
        virtual void input(std::istream&)=0;
        virtual void output(std::ostream&) const=0;
    };
 
    //Console InOut public from IOMatr
    
    class ConsoleMatr:public IOMatr
    {
    public:
        ConsoleMatr():IOMatr() {}
        ConsoleMatr(size_t n, size_t m):IOMatr(n, m) {}
        ConsoleMatr(const AbstractMatr& Ob):IOMatr(Ob) {}
        virtual ~ConsoleMatr() {}
        const ConsoleMatr& operator =(const ConsoleMatr&);
        const ConsoleMatr& operator +=(const ConsoleMatr&);
		const ConsoleMatr& operator -=(const ConsoleMatr&);
        const ConsoleMatr operator +(const ConsoleMatr&) const;
        const ConsoleMatr& operator *=(const ConsoleMatr&);
        const ConsoleMatr operator *(const ConsoleMatr&) const;
        virtual void input(std::istream&);
        virtual void output(std::ostream&) const;
    };
    
    //AbstractMatr func-members
    
    AbstractMatr::AbstractMatr(size_t n, size_t m)
    {
        Matrix.resize(n);
        for(int i=0; i!=GetRow(); ++i)
        {
            Matrix[i].resize(m);
        }
    }
 
    
    void AbstractMatr::SetSize(size_t n, size_t m)
    {
        if(GetRow()!=0&&GetCol()!=0)
            Matrix.clear();
        Matrix.resize(n);
        for(int i=0; i!=GetRow(); ++i)
        {
            Matrix[i].resize(m);
        }
    }
 
    
    void AbstractMatr::swap(AbstractMatr& Ob)
    {
        Matrix.swap(Ob.Matrix);
    }
    
    //MathMatr func-membets
    
    const MathMatr& MathMatr::operator =(const MathMatr& Ob)
    {
        MathMatr Temp(Ob);
        Temp.swap(*this);
        return *this;
    }
 
    
    const MathMatr& MathMatr::operator +=(const MathMatr& Ob)
    {
        if(GetRow()!=Ob.GetRow()&&GetCol()!=Ob.GetCol())
            throw std::invalid_argument("Size of two matrix for sum must be equal!");
        for(int i=0; i!=Ob.GetRow(); ++i)
        {
           for(int j=0; j!=Ob.GetCol(); ++j)
           {
              Matrix[i][j]+=Ob.Matrix[i][j];
           }
        }
        return *this;
    }
 
     const MathMatr& MathMatr::operator -=(const MathMatr& Ob)
    {
        if(GetRow()!=Ob.GetRow()&&GetCol()!=Ob.GetCol())
            throw std::invalid_argument("Size of two matrix for sum must be equal!");
        for(int i=0; i!=Ob.GetRow(); ++i)
        {
           for(int j=0; j!=Ob.GetCol(); ++j)
           {
              Matrix[i][j]-=Ob.Matrix[i][j];
           }
        }
        return *this;
    }

    const MathMatr MathMatr::operator +(const MathMatr& Ob) const
    {
        MathMatr Temp(*this);
        Temp+=Ob;
        return Temp;
    }
 
    const MathMatr MathMatr::operator -(const MathMatr& Ob) const
    {
        MathMatr Temp(*this);
        Temp-=Ob;
        return Temp;
    }

    const MathMatr& MathMatr::operator *=(const MathMatr& Ob)
    {
        if(GetCol()!=Ob.GetRow())
            throw std::invalid_argument("Num of 1-st matrix cols must be equal to num of 2-nd matrix rows");
        MathMatr Temp(GetRow(), Ob.GetCol());
        for(int i=0; i!=Temp.GetRow(); ++i)
        {
           for(int j=0; j!=Temp.GetCol(); ++j)
           {
              Temp.Matrix[i][j]=0;
              for(int k=0; k!=GetCol(); ++k)
              {
                 Temp.Matrix[i][j]+=Matrix[i][k]*Ob.Matrix[k][j];
              }
            }
        }
        *this=Temp;
        return *this;
    }
 
    
    const MathMatr MathMatr::operator *(const MathMatr& Ob) const
    {
        MathMatr Temp(*this);
        Temp*=Ob;
        return Temp;
    }
 
    
    void MathMatr::random_fill()
    {
       for(int i=0; i!=GetRow(); ++i)
       {
          for(int j=0; j!=GetCol(); ++j)
          {
             Matrix[i][j]=1+rand()%50;
          }
       }
    }
 
    
    std::ostream& operator <<(std::ostream& os, const MathMatr& Ob)
    {
       Ob.output(os);
       return os;
    }
 
    
    std::istream& operator >>(std::istream& is, MathMatr& Ob)
    {
       Ob.input(is);
       return is;
    }
    
    //ConsoleMatr func-members
    
    void ConsoleMatr::input(std::istream& is)
    {
       for(int i=0; i!=GetRow(); ++i)
       {
          for(int j=0; j!=GetCol(); ++j)
          {
              std::cout<<"Enter Matrix ["<<i+1<<"]["<<j+1<<"]: ";
              is>>Matrix[i][j];
          }
       }
    }
 
    
    void ConsoleMatr::output(std::ostream& os) const
    {
       for(int i=0; i!=GetRow(); ++i)
       {
          for(int j=0; j!=GetCol(); ++j)
          {
              os<<std::setw(5)<<Matrix[i][j]<<' ';
          }
          std::cout<<std::endl;
       }
    }
 
    
    const ConsoleMatr& ConsoleMatr::operator =(const ConsoleMatr& Ob)
    {
        ConsoleMatr Temp(Ob);
        Temp.swap(*this);
        return *this;
    }
 
    
    const ConsoleMatr& ConsoleMatr::operator +=(const ConsoleMatr& Ob)
    {
        if(GetRow()!=Ob.GetRow()&&GetCol()!=Ob.GetCol())
           throw std::invalid_argument("Size of two matrix for sum must be equal!");
        for(int i=0; i!=Ob.GetRow(); ++i)
        {
           for(int j=0; j!=Ob.GetCol(); ++j)
           {
              Matrix[i][j]+=Ob.Matrix[i][j];
           }
        }
        return *this;
    }
 
    
    const ConsoleMatr ConsoleMatr::operator +(const ConsoleMatr& Ob) const
    {
        ConsoleMatr Temp(*this);
        Temp+=Ob;
        return Temp;
    }
 
    
    const ConsoleMatr& ConsoleMatr::operator *=(const ConsoleMatr& Ob)
    {
        if(GetCol()!=Ob.GetRow())
            throw std::invalid_argument("Num of 1-st matrix cols must be equal to num of 2-nd matrix rows");
        ConsoleMatr Temp(GetRow(), Ob.GetCol());
        for(int i=0; i!=Temp.GetRow(); ++i)
        {
           for(int j=0; j!=Temp.GetCol(); ++j)
           {
              for(int k=0; k!=GetCol(); ++k)
              {
                 Temp.Matrix[i][j]+=Matrix[i][k]*Ob.Matrix[k][j];
              }
            }
        }
        *this=Temp;
        return *this;
    }
 
    
    const ConsoleMatr ConsoleMatr::operator *(const ConsoleMatr& Ob) const
    {
        ConsoleMatr Temp(*this);
        Temp*=Ob;
        return Temp;
    }
}
#endif