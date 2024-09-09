# project2

Αλεξία Τοπαλίδου 1115201600286
Στέφανος Μπακλαβάς 1115201700093

This project focuses on implementing algorithms for nearest neighbor search and clustering, applied to time series data. It includes:

    1.Implementation of the LSH algorithm based on the L2 metric.
    2.Implementation of random projection onto the hypercube using L2.

The project includes three main tasks:

    1.Nearest Neighbor Search using LSH, Hypercube, and Frechet methods.
    2.Clustering of time series using K-means++ for initialization.
    3.Dimensionality Reduction of time series datasets using grid filtering and Frechet distance algorithms.


Task A: Nearest Neighbor Search

    1.LSH Algorithm based on the L2 metric.
    2.Random Projection onto the hypercube with L2.

    The program takes as input a query vector q and integers N, K, and returns:

      1.The approximate nearest neighbor to q.
      2.The N nearest neighbors.
      3.The vectors within radius R from q (range search).

    Distance Metrics:

      1.Each time series is represented as a polygonal curve in R². 
        The distance between time series is calculated using the discrete Frechet metric. 
      2.The LSH algorithm is used for discrete Frechet distance.
      3.For dimensionality reduction, time series are filtered onto a grid, 
        and distances are computed using the continuous Frechet algorithm.


Task B: Clustering using K-means++

    Initialization is done using K-means++ and the following algorithms for assignment:

       1.Lloyd’s algorithm.
       2.Range search using LSH for Frechet.
       3.Range search using LSH for vectors.
       4.Range search using Hypercube.

    Update phase:

       1.Calculate the mean time series as a vector.
       2.Calculate the mean time series as a curve.

    Clustering updates are based on mean-vector or curve calculations:

       1.Assignment is exact with Lloyd's algorithm and reverse assignment via range search.
       2.LSH 
       3.Hypercube projection








Για να μεταγλωτιστεί το πρόγραμμα τρέχουμε:
make 

Για την εκτέλεση του προγράμματος και επιλογή του αντίστοιχου αλγορίθμου με παραμέτρους
μπορούμε να επιλέξουμε από τα παραδείγματα εκτέλεσης στον φάκελο commands.txt


Για να τρέξουμε το testing:
χρειάζεται να έχουμε το google testing framework και cmake.Το testing βρίσκεται μέσα στον φάκελο test
cd test
cmake CMakeLists.txt
make
./executeTests


Extra comments

Στην παρούσα εργασία υλοποιήθηκαν όλα τα ζητούμενα.

Parameter w:

    w is automatically set to 600. This value provides better distribution of points across buckets, 
    leading to more balanced bucket filling. As a result, only a few buckets contain the majority of 
    the dataset points, facilitating both LSH and Hypercube algorithms.



  Discrete Frechet Algorithm for 2D Curves:

    The Discrete Frechet algorithm was implemented for 2D curves. Each curve from the dataset is 
    treated as lacking a time coordinate (x). To address this, time steps are added incrementally 
    as each line from the input file is processed. After creating the grid_curve, consecutive duplicate
    points are removed, followed by padding. Although hashing is performed on this grid curve, the 
    original vector is stored in the data structure. For queries, the same process is followed, 
    but the Frechet distances are calculated based on the original input curves.
    The value for e is set to 1.2. With this value, the curve lengths are reduced by approximately 40%, 
    while approximate nearest neighbors are always found. 

Continuous Frechet Algorithm for 1D Curves

    The Continuous Frechet algorithm was implemented for 1D curves. Each vector undergoes filtering
    based on the constant e, set to 0.05 in this case.A grid_curve is then created, followed by min_max_filtering. 
    This final curve is hashed and is typically less than half the length of the original.
    The original curve from the input file is stored in the structure. For queries, significant filtering 
    is necessary for the Continuous Frechet algorithm because the distance calculation function is time-consuming.
	 
	 

Question B: Clustering and Frechet-Based Algorithms


Key Observations:

    The value of e is 1.2, and the value of δ is 1.0.
    When using the lsh_frechet algorithm, due to the large length of the curves, filtering 
    is applied in the Exact_Lloyd phase. During each step, when two nodes of the clustering 
    tree are combined to form a new mean curve, e_filtering is applied. If this is insufficient, 
    min_max_filtering is performed as well.
    Due to the high degree of randomness, it is possible that during the Range Search Clustering, 
    some points may not be assigned to a cluster via LSH 
    and will be assigned later using Lloyd’s algorithm.
    The criteria for terminating the Range_Search_Clustering radius doubling and proceeding to the next iteration are:
        a. 70% of the dataset points must be assigned to clusters.
        b. No cluster has any points.
        c. The radius reaches 10 times the distance between the most distant centroids selected using K-means++.

	
		
		
	
	
	
	
	
	
