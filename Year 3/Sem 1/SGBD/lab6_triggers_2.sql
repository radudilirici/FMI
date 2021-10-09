drop table info_dept_dlr;
create table  info_dept_dlr
(id number(3) primary key,
nume_dept varchar2(50),
plati number);

insert into info_dept_dlr
select max(department_id), department_name, nvl(sum(salary),0)
from departments
left outer join employees
using (department_id)
group by department_name;

select * from info_dept_dlr;

create or replace procedure modific_plati_dlr
    (v_cod_dep info_dept_dlr.id %type,
     v_dif_plata info_dept_dlr.plati%type) as
begin
    update info_dept_dlr
    set plati = nvl(plati, 0) + v_dif_plata
    where id = v_cod_dep;
end;
/

create or replace trigger trig1_dlr
    after delete or update or insert of salary on emp_dlr
    for each row
begin
    if deleting then
        modific_plati_dlr(:new.department_id, :new.salary * (-1));
    elsif inserting then
        modific_plati_dlr(:new.department_id, :new.salary);
    else -- updating
        modific_plati_dlr(:new.department_id, :new.salary - :old.salary);
    end if;
end;
/

select * from emp_dlr;
select * from info_dept_dlr
order by 1;

INSERT INTO emp_dlr(employee_id, last_name, email, hire_date, 
                     job_id, salary, department_id) 
VALUES (301, 'N1', 'n1@g.com',sysdate, 'SA_REP', 2, 90);


