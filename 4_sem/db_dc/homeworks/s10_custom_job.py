from pyspark import SparkContext, SparkConf

if __name__ == "__main__":
    conf = SparkConf().setAppName("WordCount")
    sc = SparkContext(conf=conf)
    input_dir="s3a://demo/input/*" #2476
    input_files = sc.textFile(input_dir)

    words = input_files.flatMap(lambda line: line.split(" "))
    word_counts = words.map(lambda word: (word, 1)).reduceByKey(lambda a,b: a+b)
    print("Z"*100)
    #print(word_counts)
    print("X"*100)
    word_counts.saveAsTextFile("s3a://demo/output/file.txt")
