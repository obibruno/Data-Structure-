//
//  CDA.cpp
//  phase1
//
//  Created by Obi Bruno Da Silva Ndubueze on 2/9/21.
//
#include <cstdlib>   // rand and srand
#include <ctime>
#include <iostream>

using namespace std;
template<class elmtype>

class CDA
{
    private:
        int size, capacity, front;
        elmtype *a;
        bool reverse, reverseCall;
    
    public:
        CDA()
        {
            a = new elmtype[capacity = 1];
            front  = size = 0;
            reverse = reverseCall = false;
        }
        CDA(int s)
        {
            a = new elmtype[size = capacity = s];
            front  = 0;
            reverse = reverseCall = false;
        }
        CDA(const CDA &other)
        {
            size = other.size;
            capacity = other.capacity;
            reverse = other.reverse;
            a = new elmtype[capacity];
            for(int i = 0; i < size; i++)
            {
                a[i] = other.a[(other.front + i) % other.capacity];
            }
            front = 0;
        }
        ~CDA()
        {
            delete[] a;
            a = NULL;
        }
        CDA& operator = (const CDA &other)
        {
            size = other.size;
            capacity =  other.capacity;
            reverse = other.reverse;
            delete [] a;
            a = new elmtype[capacity];
            for(int i = 0; i < size; i++)
            {
                a[i] = other.a[(other.front + i) % other.capacity];
            }
            front = 0;
            return *this;
        }
        
        elmtype& operator[](int i)
        {
            if (i < 0 || i >= size)
            {
                cout << "Out of bounds reference: " << i << endl;
                return a[front]; // FIX ME!!!!!!!!
            }
            if (reverse == true)
            {
                
                return a[((size - 1 - i) + front) % capacity];  //capacity - current location = reverse location
            }
            else{
                return a[(front + i) % capacity];
            }
        }
        void AddEnd(int v)
        {
            if (reverse == true && reverseCall == false)
            {
                reverseCall = true;
                AddFront(v);
                return;
            }
            reverseCall = false;
       
            if (size == capacity)
            {
                elmtype *temp = new elmtype[capacity * 2];

                for (int z = 0; z < size; z++)
                {
                    temp[z] = a[(front + z)%capacity];
                }
                capacity *= 2;
                temp[size] = v;
                delete [] a;
                a = temp;
                front = 0;
                size++;
            }
            else
            {
                a[(front + size)%capacity] = v;
                size++;
            }
        }
        void AddFront(int v)
        {
            if (reverse == true && reverseCall == false)
            {
                reverseCall = true;
                AddEnd(v);
                return;
            }
        
            if (size == capacity)
            {
                elmtype *temp = new elmtype[capacity * 2];
                temp[0] = v;
                for (int z = 0; z < size; z++)
                {
                    temp[z + 1] = a[(front + z)%capacity];
                }
                capacity *= 2;
                delete [] a;
                a =  temp;
                front = 0;
            }
            else
            {
                if (front == 0)
                {
                    a[(capacity +(front-1)%capacity)] = v;
                    front = (capacity +(front-1)%capacity);
                }
                else
                {
                    a[(front - 1) % capacity] = v;
                    front = (front -1) % capacity;
                    
                }
            }
            reverseCall = false;
            size++;
        }
        void DelEnd()
        {
            if (reverse == true && reverseCall == false)
            {
                reverseCall = true;
                DelFront();
                return;
            }
            if( size <= (capacity/4) && capacity && size> 7)
            {
                elmtype *temp = new elmtype[capacity/2];
                for (int z = 0; z < size; z++)
                {
                    temp[z] = a[(front + z)%capacity];
                }
                capacity /= 2;
                delete [] a;
                a = temp;
                front = 0;
            }
            reverseCall = false;
            size --;
        }
        void DelFront()
        {
            if (reverse == true && reverseCall == false)
            {
                reverseCall = true;
                DelEnd();
                return;
            }
            size --;
            reverseCall = false;
            front = (front + 1 )%capacity;
            if( size <= (capacity/4) && size> 7)
            {
                elmtype *temp = new elmtype[capacity/2];
                for (int z = 0; z < size ; z++)
                {
                    temp[z] = a[(front + z)%capacity];
                }
                capacity /= 2;
                delete[] a;
                a = temp;
                front = 0;
            }
            
        }
        int Length() { return size;}
        int Capacity() {return capacity;}
        void Clear()
        {
            delete a;
            a = new elmtype[capacity=4];
            size = front = 0;
            reverse = reverseCall = false;
        }
        void Reverse()
        {
            if (reverse == false) { reverse = true;}
            else { reverse = false;}
        }
    
        int Search(elmtype e)
        {
            for (int i = 0; i < size; i++)
            {
                if (a[(front + i) % capacity] == e)
                {
                    if (reverse == true)
                    {
                        return size - 1 - i; //capacity - current location = reverse location
                    }
                    else
                    {
                        return i;
                    }
                }
            }
            return -1;
        }

        int BinSearch(elmtype e)
            {
                int left = 0;
                int right = size - 1;
                int mid;

                while(left <= right)
                {
                    mid = left + (right - left) / 2;
                    if(a[(front + mid) % capacity] == e)
                    {
                        return mid;
                    }
                    else if(e < a[(front + mid) % capacity])
                    {
                        right = mid - 1;
                    }
                    else
                    {
                        left = mid + 1;
                    }

                    if (a[(front + left) % capacity] > e)
                    {
                        return ~left;
                    }
                }                     
                return ~size;
            }
    
        void Sort()
        {
            if(reverse == true){ reverse = false;}
            mergeSort(0, size - 1);
            
        }
        void merge(int l, int m, int r)
        {
            int i, j, k, nl, nr;

            nl = m-l+1;
            nr = r-m;

            elmtype larray[nl], rarray[nr];

            for(i = 0; i<nl; i++) larray[i] = a[(front+l+i) % capacity];
            for(j = 0; j<nr; j++) rarray[j] = a[(front+m+1+j)%capacity];

            i = 0; j = 0; k = l;

            while(i < nl && j < nr)
            {
                if(larray[i] <= rarray[j])
                {
                    a[(front+k)%capacity] = larray[i];
                    i++;
                }
                else
                {
                    a[(front+k)%capacity] = rarray[j];
                    j++;
                }
                k++;
            }
            while(i < nl)
            {
                a[(front+k)%capacity] = larray[i];
                i++; k++;
            }
            while(j < nr)
            {
                a[(front+k)%capacity] = rarray[j];
                j++; k++;
            }
        }

        void mergeSort(int l, int r)
        {
            if(l < r)
            {
                int m = l+(r-l)/2;

                mergeSort(l, m);
                mergeSort(m+1, r);
                merge(l, m, r);
            }
        }
        int partition(elmtype* tempA, int l, int r)
        {
            elmtype x = tempA[r];
            int i = l;
            elmtype swapTemp;
        
            for (int j = l; j <= r - 1 ; j++)
            {
                if (tempA[j] <= x)
                {
                    swapTemp = tempA[i];
                    tempA[i] = tempA[j];
                    tempA[j] = swapTemp;

                    i++;
                }
            }
            swapTemp = tempA[i];
            tempA[i] = tempA[r];
            tempA[r] = swapTemp;
            
            return i;
        }
    
        int random(elmtype* tempA, int l, int r)
        {
            srand(time(NULL));
            int random = l + rand() % (r - l + 1);
            elmtype swapTemp = tempA[random];
            tempA[random] = tempA[r];
            tempA[r] = swapTemp;
            return partition(tempA, l, r);
        }
    
        elmtype Select(int k)
        {
            elmtype * tempA = new elmtype[capacity];
            for(int i = 0; i < size; i++)
            {
                tempA[i] = a[(front + i)%capacity];
            }
            
            int l = 0;
            int r = size - 1;
            
            while (l <= r) {
                    int index = random(tempA, l, r);

                    if (index == k - 1)
                    {
                        return tempA[index];
                    }
                    else if (index > k - 1)
                    {
                        r = index - 1;
                    }
                    else
                    {
                        l = index + 1;
                    }
                }
                return -1;
        }
};
