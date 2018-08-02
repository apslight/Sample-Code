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
( 0, 1, 8, 8), ( 0, 5, 10, 10), ( 0, 7, 5, 5), ( 1, 5, 4, 4), 
( 1, 7, 4, 4), ( 1, 2, 4, 4), ( 1, 4, 4, 4), ( 2, 5, 3, 3), 
( 2, 3, 3, 3), ( 3, 5, 6, 6), ( 3, 4, 1, 1), ( 3, 6, 2, 2), 
( 4, 6, 3, 3), ( 6, 7, 3, 3);   

SELECT * FROM pgr_kruskal(
    'SELECT id, source, target, cost, reverse_cost FROM edge_table'
);
                          
/************************ OUTPUT ****************************** 
  seq | component | edge | cost | tree_cost 
-----+-----------+------+------+-----------
    1 |         0 |   11 |    1 |         1
    2 |         0 |   12 |    2 |         3
    3 |         0 |   14 |    3 |         6
    4 |         0 |    8 |    3 |         9
    5 |         0 |    9 |    3 |        12
    6 |         0 |    7 |    4 |        16
    7 |         0 |    3 |    5 |        21
(7 rows)
***************************************************************/
