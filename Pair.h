template <class A, class B> class Pair{

    private:

        A first;
        B second;

    public:

        Pair(A v1, B v2){
            first = v1;
            second = v2;
        }

        A GetFirst(){
            return first;
        }

        B GetSecond(){
            return second;
        }

        void SetFirst(A val){
            first = val;
        }

        void SetSecond(B val){
            second = val;
        }
};
