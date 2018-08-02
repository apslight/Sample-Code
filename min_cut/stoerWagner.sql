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
( 0, 1, 2, 2), ( 0, 4, 3, 3), ( 1, 4, 2, 2), ( 1, 5, 2, 2), 
( 1, 2, 3, 3), ( 2, 6, 2, 2), ( 2, 3, 4, 4), ( 3, 6, 2, 2), 
( 3, 7, 2, 2), ( 4, 5, 3, 3), ( 5, 6, 1, 1), ( 6, 7, 3, 3);  

SELECT * FROM pgr_stoerWagner(
    'SELECT id, source, target, cost, reverse_cost FROM edge_table'
);     
                 
/************************ OUTPUT ****************************** 
 seq | edge | cost | mincut 
-----+------+------+--------
   1 |    5 |    3 |      3
   2 |   11 |    1 |      4
(2 rows)
***************************************************************/
