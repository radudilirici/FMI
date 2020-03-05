-- Laborator 1

SELECT * FROM COUNTRIES;
DESCRIBE EMPLOYEES;
DESC employees;  -- acelasi lucru

SELECT employee_id as "cod angajat", salary FROM employees;  -- nu sunt necesare "" daca nu avem spatiu. 'as' e optional
-- 6
SELECT DISTINCT job_id FROM employees;  -- cand nu folosim DISTINCT e echivalent cu ALL
-- 7
SELECT last_name || ', ' || job_id "Angajat si titlu" FROM employees;
-- 8
SELECT employee_id || ', ' || first_name || ', ' || last_name "etc etc" FROM employees;
-- 9
SELECT last_name, salary FROM employees WHERE salary > 2850 ORDER BY salary DESC;
SELECT last_name, salary FROM employees WHERE salary BETWEEN 2100 AND 2500 ORDER BY salary ASC;  -- salary >= . AND salary <= .
-- 10
SELECT last_name, department_id FROM employees WHERE employee_id = 104;  -- '=', nu '=='
-- 11
SELECT last_name, salary FROM employees WHERE salary NOT BETWEEN 1500 AND 2850 ORDER BY salary;
-- 12
SELECT sysdate FROM dual;  -- ca sa vad formatul curent al serverului
SELECT last_name, job_id, hire_date FROM employees WHERE hire_date BETWEEN '20-FEB-1987' AND '1-MAY-1989' ORDER BY hire_date;
-- 13
SELECT last_name, department_id FROM employees WHERE department_id IN (10, 30) ORDER BY last_name;
-- 14
SELECT last_name "Angajat", salary "Salariu lunar" FROM employees WHERE salary >= 3500 AND department_id IN (10, 30);
-- 15
SELECT TO_CHAR(sysdate, 'YYYY, MONTH, DD, HH24:MI:SS') FROM dual;
-- 16
SELECT last_name, hire_date FROM employees WHERE hire_date LIKE '%87%';  -- se uita se fie 87 oriunde in string
SELECT last_name, hire_date FROM employees WHERE TO_CHAR(hire_date, 'YYYY') = 1987;  -- nu sunt obligatorii '' la 1987
-- 17
SELECT last_name, job_id FROM employees WHERE manager_id IS NOT NULL;  -- trebuie sa pun IS cand verific daca e NULL
-- 18
SELECT commission_pct FROM employees ORDER BY commission_pct;  -- NULL e cel mai mare
-- 20
SELECT last_name FROM employees WHERE LOWER(last_name) LIKE('__a%');  -- % poate sa insemne si sirul vid
-- 21
SELECT last_name, department_id, manager_id FROM employees WHERE LOWER(last_name) LIKE('%l%l%') AND (department_id = 80 OR manager_id = 121);
-- 22 de vazut JOIN
SELECT last_name, job_id, salary FROM employees WHERE (LOWER(job_id) LIKE '%clerk%' OR LOWER(job_id) LIKE 'rep') AND salary NOT IN (1000, 2000, 3000);
-- 23
SELECT last_name, salary, commission_pct FROM employees WHERE salary > salary * commission_pct * 5 AND commission_pct IS NOT NULL;
