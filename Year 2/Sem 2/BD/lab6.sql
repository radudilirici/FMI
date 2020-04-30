-- 17
select last_name, department_id, salary
from employees
where hire_date > to_date('&in_date');

-- 19
accept data1 prompt 'data inceput = ';
accept data2 prompt 'data final = ';
select last_name || ', ' || job_id Angajati, to_char(hire_date, 'MM/DD/YY')
from employees
where to_date('&data1', 'MM/DD/YY') < hire_date and hire_date < to_date('&data2', 'MM/DD/YY');