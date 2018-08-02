DROP TABLE IF EXISTS edge_table;
CREATE TABLE edge_table(
                  id BIGSERIAL,
                  source BIGINT,
                  target  BIGINT,
                  cost  FLOAT,
                  reverse_cost FLOAT
                 );

INSERT INTO edge_table(
                   source, target, cost, reverse_cost
                   ) VALUES 
( 0, 1, 8, 8), ( 0, 5, 10, 10), ( 0, 7, 4, 4), ( 1, 5, 7, 7), 
( 1, 7, 9, 9), ( 1, 2, 4, 4), ( 1, 4, 10, 10),( 2, 5, 3, 3), 
( 2, 3, 3, 3), ( 3, 5, 18, 18), ( 3, 4, 25, 25), ( 3, 6, 2, 2), 
( 4, 6, 7, 7), ( 4, 5, 2, 2), ( 6, 7, 3, 3); 

/* Signature 1 (Without root vertex) */
SELECT * FROM pgr_prim(
    'SELECT id, source, target, cost, reverse_cost FROM edge_table'
);                              

/************************ OUTPUT ****************************** 
 seq | root_vertex | node | edge | cost | agg_cost | tree_cost 
-----+-------------+------+------+------+----------+-----------
   1 |           0 |    0 |   -1 |    0 |        0 |         0
   2 |           0 |    7 |    3 |    4 |        4 |         4
   3 |           0 |    6 |   15 |    3 |        7 |         7
   4 |           0 |    3 |   12 |    2 |        9 |         9
   5 |           0 |    2 |    9 |    3 |       12 |        12
   6 |           0 |    5 |    8 |    3 |       15 |        15
   7 |           0 |    4 |   14 |    2 |       17 |        17
   8 |           0 |    1 |    6 |    4 |       16 |        21
(8 rows)
***************************************************************/



/* Signature 2 (Withroot vertex) */
SELECT * FROM pgr_prim(
    'SELECT id, source, target, cost, reverse_cost FROM edge_table', 4
);

/************************ OUTPUT ****************************** 
 seq | root_vertex | node | edge | cost | agg_cost | tree_cost 
-----+-------------+------+------+------+----------+-----------
   1 |           4 |    4 |   -1 |    0 |        0 |         0
   2 |           4 |    5 |   14 |    2 |        2 |         2
   3 |           4 |    2 |    8 |    3 |        5 |         5
   4 |           4 |    3 |    9 |    3 |        8 |         8
   5 |           4 |    6 |   12 |    2 |       10 |        10
   6 |           4 |    7 |   15 |    3 |       13 |        13
   7 |           4 |    1 |    6 |    4 |        9 |        17
   8 |           4 |    0 |    3 |    4 |       17 |        21
(8 rows)
***************************************************************/



