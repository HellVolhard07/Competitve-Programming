template <typename V>
class mapnode {
    string key;
    V val;
    mapnode* next;
    
    mapnode(string key, V val) {
        this->key = key;
        this->val = val;
        this->next = NULL;
    }
    
    ~mapnode() {
        delete next;
    }
}

template <typename V>
class ourmap {
    mapnode<V>** buckets;
    int count;
    int numBuckets;
    
    int getBucketIndex(string key) {
        int hashCode = 0;
        
        int currentCoeff = 1;
        for(int i = key.length() - 1 ; i >= 0 ; i--) {
            hashCode += key[i] * currentCoeff;
            hashCode %= numBuckets;
            currentCoeff *= 37;
            currentCoeff %= numBuckets;
        }
        
        return hashCode % numBuckets;
    }
    
    void rehash() {
        mapnode<V>** temp = buckets;
        buckets = new mapnode<V>* [numBuckets * 2];
        for(int i = 0 ; i < 2 * numBuckets ; i++) {
            buckets[i] = NULL;
        }
        int oldBucketCount = numBuckets;
        numBuckets = 2 * numBuckets;
        count = 0;
        
        for(int i = 0 ; i < oldBucketCount ; i++) {
            mapnode<V>* head = temp[i];
            while(head) {
                string key = head->key;
                V val = head->val;
                insert(key, val);
                head = head->next;
            }
        }
        
        for(int i = 0 ; i < oldBucketCount ; i++) {
            delete temp[i];
        }
        
        delete [] temp;
    }
    
    public: 
    ourmap() {
        count = 0;
        numBuckets = 20;
        buckets = new mapnode<V>* [numBuckets];
        for(int i = 0 ; i < numBuckets ; i++) {
            buckets[i] = NULL;
        }
    }
    
    ~ourmap() {
        for(int i = 0 ; i < numBuckets ; i++) {
            delete buckets[i];
        }
        
        delete [] buckets;
    }
    
    int size() {
        return count;
    }
    
    void insert(string key, V val) {
        int bucketIndex = getBucketIndex(key);
        
        mapnode<V>* head = buckets[bucketIndex];
        while(head) {
            if(head->key == key) {
                head->val = val;
                return;
            }
            else {
                head = head->next;    
            }
        }
        head = buckets[bucketIndex];
        mapnode<V>* node = new mapnode<V> (key, val);
        node->next = head;
        buckets[bucketIndex] = node;
        count++;
        
        double loadFactor = (1.0 * count) / numBuckets;
        if(loadFactor > 0.7) {
            rehash();
        }
    }
    
    V getVal(string key) {
        int bucketIndex = getBucketIndex(key);
        mapnode<V>* head = buckets[bucketIndex];
        while(head) {
            if(head->key == key) {
                return head->val;
            }
            else {
                head = head->next;
            }
        }
        return 0;
    }
    
    V remove(string key) {
        int bucketIndex = getBucketIndex(key);
        mapnode<V>* head = buckets[bucketIndex];
        mapnode<V>* prev = NULL;
        while(head) {
            if(head->key == key) {
                if(prev == NULL) {
                    buckets[bucketIndex] = head->next;
                }
                else {
                    prev->next = head->next;
                }
                V val = head->val;
                head->next = NULL;
                delete(head);
                count--;
                return val;
            }
            else {
                prev = head;
                head = head->next;
            }
        }
        return 0;
    }
}
