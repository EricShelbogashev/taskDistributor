## Usage
```
mpiexec -n <process_number> --oversubscribe <path>/taskDistributor <path>/input.txt <path>/output.txt
```
## Example input
`input.txt`
```
4 23 0
93	30	89	91	97	41	86	35	21	89	21	23	38	77	95	43	86	73	97	25	57	96	74
23	36	93	88	100	40	15	7	21	86	45	42	4	52	22	56	87	6	39	9	2	69	63
83	74	21	16	85	77	98	37	38	75	12	37	43	61	90	57	72	40	10	85	53	52	70
96	62	47	53	39	17	88	59	53	69	77	27	33	12	45	99	77	27	69	83	25	39	5
23 17 1
17	87	34	53	13	86	90	34	85	58	54	7	76	79	37	86	45
40	90	80	53	25	67	89	28	75	57	22	94	64	38	83	97	57
27	92	88	88	81	91	81	75	79	21	23	4	35	85	27	16	71
14	65	41	9	85	32	82	63	25	60	88	96	6	54	75	48	12
44	38	16	11	26	63	44	52	41	70	95	78	21	99	38	65	63
19	76	19	72	76	95	96	19	23	90	19	13	28	100	1	88	75
17	68	30	81	56	91	38	18	63	1	41	2	78	56	33	48	93
91	39	20	68	6	60	69	12	76	84	31	33	6	11	52	24	75
11	84	18	18	85	15	21	64	83	28	13	89	59	27	27	43	14
88	4	94	9	89	95	16	15	89	31	92	90	99	51	48	34	95
27	74	72	16	87	4	57	1	1	79	71	10	57	86	76	1	80
12	30	83	53	17	79	98	7	17	55	37	47	31	83	95	73	53
76	20	33	5	35	8	78	15	74	84	44	65	76	48	67	66	86
60	91	57	64	18	4	57	77	55	13	76	39	17	53	19	65	62
45	67	60	96	7	39	99	85	95	48	65	90	63	80	10	37	78
34	2	95	100	79	31	17	32	11	81	39	40	4	74	44	6	23
11	67	81	74	35	11	11	97	40	52	26	29	32	71	20	11	50
84	69	66	18	82	76	60	89	77	63	98	96	54	48	91	88	52
96	32	47	4	14	69	80	99	93	72	66	17	72	72	44	83	63
60	65	46	92	78	77	20	46	7	13	23	77	70	100	45	77	61
78	3	98	86	74	13	69	34	33	1	22	42	77	55	34	81	90
3	83	68	61	29	2	14	78	14	67	26	70	9	24	3	2	47
80	40	79	5	98	21	19	9	4	50	71	76	56	48	44	42	53
```
`output.txt`
```
66847 84118 85782 71301 72827 74871 82672 78696 80858 73015 81892 76716 69891 93463 58253 73759 90500 
38610 57075 62883 45158 55564 48655 51138 50587 45633 53147 55627 53644 39534 66783 41148 42183 57258 
56202 72791 72241 71205 63936 68188 68903 56144 65332 61359 62815 69579 64986 83472 50329 69709 81463 
49890 67098 68980 63821 61829 63489 63735 54070 62956 61511 57441 57300 60123 77476 53773 56781 71437 
```
