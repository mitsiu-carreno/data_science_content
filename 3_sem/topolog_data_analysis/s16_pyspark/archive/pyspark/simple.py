# importing necessary libraries
import pyspark
from pyspark.sql import SparkSession

# function to create new SparkSession
def create_session():
	spk = SparkSession.builder \
		.master("local") \
		.appName("employee_profile.com") \
		.getOrCreate()
	return spk


def create_df(spark, data, schema):
	df1 = spark.createDataFrame(data, schema)
	return df1


if __name__ == "__main__":

	# calling function to create SparkSession
	spark = create_session()

	input_data = [(1, "Shivansh", "Data Scientist", "Noida"),
				(2, "Rishabh", "Software Developer", "Bangalore"),
				(3, "Swati", "Data Analyst", "Hyderabad"),
				(4, "Amar", "Data Analyst", "Noida"),
				(5, "Arpit", "Android Developer", "Pune"),
				(6, "Ranjeet", "Python Developer", "Gurugram"),
				(7, "Priyanka", "Full Stack Developer", "Bangalore")]

	schema = ["Id", "Name", "Job Profile", "City"]

	# calling function to create dataframe
	df = create_df(spark, input_data, schema)

	# retrieving all the elements of
	# the dataframe using collect()
	# Storing in the variable
	data_collect = df.collect()

	df.show()
