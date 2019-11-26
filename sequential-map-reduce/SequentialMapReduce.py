from sklearn.datasets import fetch_20newsgroups
from sklearn.feature_extraction.stop_words import ENGLISH_STOP_WORDS

import time
import collections
import re 
from functools import reduce

news = twenty_train = fetch_20newsgroups(subset='train')
data = news.data*2

def clean_word(word):
    return re.sub(r'[^\w\s]','',word).lower()
        
def word_not_in_stopwords(word):
    return word not in ENGLISH_STOP_WORDS and word and word.isalpha()

def chunkify(l, n):
    # For item i in a range that is a length of l,
    for i in range(0, len(l), n):
        # Create an index range for l of n items:
        yield l[i:i+n]
    
def find_top_words(data):
    cnt = collections.Counter()
    for text in data:
        tokens_in_text = text.split()
        tokens_in_text = map(clean_word, tokens_in_text)
        tokens_in_text = filter(word_not_in_stopwords, tokens_in_text)
        cnt.update(tokens_in_text)
        
    return cnt.most_common(10)

def mapper(text):
    tokens_in_text = text.split()
    tokens_in_text = map(clean_word, tokens_in_text)
    tokens_in_text = filter(word_not_in_stopwords, tokens_in_text)
    return collections.Counter(tokens_in_text)
def reducer(cnt1, cnt2):
    cnt1.update(cnt2)
    return cnt1
def chunk_mapper(chunk):
    mapped = map(mapper, chunk)
    reduced = reduce(reducer, mapped)
    return reduced


start_time = time.time()

print(find_top_words(data))

elapsed_time = time.time() - start_time
print(elapsed_time,'s')