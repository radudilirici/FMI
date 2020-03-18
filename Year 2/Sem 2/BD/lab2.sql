-- Laborator 2

-- 1
SELECT first_name || ' ' || last_name || ' castiga ' || salary || ' lunar dar doreste ' || salary * 3 "Salariu ideal" FROM employees;
-- 2.1
SELECT INITCAP(first_name) || ' ' || UPPER(last_name) || ' ' || LENGTH(last_name)
FROM employees
WHERE REGEXP_LIKE(last_name, '^[JM]|^..A', 'i');
-- 2.2
SELECT INITCAP(first_name) || ' ' || UPPER(last_name) || ' ' || LENGTH(last_name)
FROM employees
WHERE SUBSTR(UPPER(last_name), 1, 1) = 'J'
    OR SUBSTR(UPPER(last_name), 1, 1) = 'M'
    OR SUBSTR(UPPER(last_name), 3, 1) = 'A';
-- 3
SELECT employee_id, TRIM(BOTH FROM last_name), department_id
FROM employees
WHERE UPPER(first_name) = 'STEVEN';
-- 4
SELECT employee_id, last_name, DECODE(INSTR(UPPER(last_name), 'A'), 0, 'Nu exista', INSTR(UPPER(last_name), 'A')) "Priuml A"
FROM employees
WHERE UPPER(last_name) LIKE '%E';
-- 5
SELECT first_name, MOD(FLOOR(sysdate - (hire_date)), 7) "Rest"
FROM employees
WHERE MOD(FLOOR(sysdate - (hire_date)), 7) = 0;
-- 6
SELECT employee_id, last_name, salary, ROUND(salary * 1.15001, 2), ROUND(salary / 10000, 2)
FROM employees;
-- 7
SELECT last_name "Nume angajat", hire_date "Data angajarii"
FROM employees
WHERE commission_pct IS not null;
-- 8
SELECT TO_CHAR(sysdate + 30, 'MONTH, DD, YYYY, HH24:MI:SS') FROM dual;
-- 9
SELECT TO_DATE('31-DEC-' || TO_CHAR(sysdate, 'YYYY')) - sysdate "Zile ramase" FROM dual;
-- 10 a)
SELECT TO_CHAR(sysdate + 1/2, 'DD/MM/YYYY, HH24:MI') FROM dual;
-- 10 b)
SELECT TO_CHAR(sysdate + 1/24/60*5, 'DD/MM/YYYY, HH24:MI') FROM dual;
-- 11
SELECT first_name || ' ' || last_name, hire_date,
TO_CHAR(NEXT_DAY(ADD_MONTHS(hire_date, 6), 'Monday'), 'DD-MON-YY') "Negociere"
FROM employees;
-- 12
SELECT last_name, ROUND(MONTHS_BETWEEN(sysdate, hire_date)) "Luni lucrate" FROM employees
ORDER BY  "Luni lucrate";
-- 13
SELECT last_name, hire_date, TO_CHAR(hire_date, 'DAY') "Zi" FROM employees
ORDER BY "Zi";
-- 14
SELECT last_name, DECODE(commission_pct, null, 'Fara comision', commission_pct) "Comision" FROM employees;
-- 15
SELECT last_name, salary FROM employees WHERE salary > 10000;
-- 16
SELECT last_name, job_id, salary, 
CASE job_id
WHEN 'IT_PROG' THEN salary * 1.2
WHEN 'SA_REP' THEN salary * 1.25
WHEN 'SA_MAN' THEN salary * 1.35
ELSE salary
END AS "Salariu negociat"
FROM employees;
-- 17
SELECT employees.last_name, employees.department_id, departments.department_name FROM employees
JOIN departments ON employees.department_id = departments.department_id;
-- 18
SELECT department_name FROM departments WHERE department_id = 30;
-- 19
SELECT employees.last_name, departments.department_name, locations.city
FROM employees
JOIN departments ON employees.department_id = departments.department_id
JOIN locations ON locations.location_id = departments.location_id
WHERE employees.commission_pct is not null;
-- 20
SELECT employees.last_name, departments.department_name
FROM employees
JOIN departments ON departments.department_id = employees.department_id
WHERE UPPER(employees.last_name) LIKE '%A%';
-- 21
SELECT last_name, job_title, departments.department_id, department_name
FROM employees
JOIN departments ON departments.department_id = employees.department_id
JOIN jobs ON jobs.job_id = employees.job_id
JOIN locations ON locations.location_id = departments.location_id
WHERE UPPER(locations.city) = 'OXFORD';
-- 22
SELECT F.employee_id "#Ang", F.last_name "Angajat", F.manager_id "#Mgr", S.last_name "Manager"
FROM employees F
JOIN employees S ON F.manager_id = S.employee_id;
-- 23
SELECT F.employee_id "#Ang", F.last_name "Angajat", F.manager_id "#Mgr", S.last_name "Manager"
FROM employees F
LEFT JOIN employees S ON F.manager_id = S.employee_id;
-- 24
SELECT S.last_name "Angajat", S.department_id "Departament", F.last_name "Coleg"
FROM employees F
JOIN employees S on F.department_id = S.department_id and S.last_name != F.last_name;
-- 25
SELECT last_name, jobs.job_id, job_title, department_name, salary
FROM employees
JOIN jobs ON jobs.job_id = employees.job_id
JOIN departments ON employees.department_id = departments.department_id;
-- 26
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date FROM employees WHERE UPPER(last_name) = 'GATES');
-- 27
SELECT F.last_name "Angajat", F.hire_date "Data_ang", S.last_name "Manager", S.hire_date "Data_mgr"
FROM employees F
JOIN employees S ON F.manager_id = S.employee_id
WHERE F.hire_date < S.hire_date;