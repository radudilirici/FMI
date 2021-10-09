-- Definiți un declanșator cu ajutorul căruia să se implementeze restricția conform căreia
-- într-un departament nu pot lucra mai mult de 45 persoane
-- (se vor utiliza doar tabelele emp_* și dept_* fără a modifica structura acestora).

set serveroutput on;

select * from emp_dlr;

select department_id, count(1)
from emp_dlr
group by department_id
order by 1;

create or replace trigger trigger_dlr
    before insert or update on emp_dlr
    for each row
declare
    nr_in_dept number(3);
begin
    select count(1)
    into nr_in_dept
    from emp_dlr
    where department_id = :new.department_id;
    
    if nr_in_dept >= 45 then
        raise_application_error(-20001, 'prea multi anagajati in departamentul '|| :new.department_id);
    end if;
end;
/

insert into emp_dlr (employee_id, last_name, department_id, email, hire_date, job_id)
values (207, 'test', 50, 'wqedsa@dsa.com', sysdate, 'IT_PROG');


--- pesti

CREATE OR REPLACE PACKAGE pesti_pachet AS
    TYPE tablou_acv is table of acvariu.cod_acvariu%type INDEX BY PLS_INTEGER;
    
    TYPE t_pesti_acv is table of tablou_acv INDEX BY PLS_INTEGER;

    
    TYPE tip_pesti IS
        TABLE OF peste.cod_peste%type INDEX BY PLS_INTEGER;
        
    pesti tip_pesti;
    acvarii t_pesti_acv;
    
END;


CREATE OR REPLACE TRIGGER trig_pesti1 BEFORE
    INSERT OR UPDATE ON crescut
BEGIN
    select cod_peste
    BULK COLLECT
    INTO pesti_pachet.pesti
    from peste;
    
    
    FOR i IN 1..pesti_pachet.pesti.last LOOP
    
        select cod_acvariu
        BULK COLLECT
        INTO pesti_pachet.acvarii(i)
        from crescut
        where cod_peste = pesti_pachet.pesti(i) ;
    
    END LOOP;

    
END;

CREATE OR REPLACE TRIGGER trig_pesti2 BEFORE
    INSERT OR UPDATE ON crescut
    FOR EACH ROW
BEGIN
    FOR i IN 1..pesti_pachet.pesti.last LOOP
        IF pesti_pachet.pesti(i) = :new.cod_peste then
            
            FOR j IN 1..pesti_pachet.acvarii(i).last LOOP
            
                    IF pesti_pachet.acvarii(i)(j) = :new.cod_acvariu then
                        raise_application_error(-20000, 'Eroare');
                    end if;
    
             END LOOP;
             
     
             pesti_pachet.acvarii(i).extend;
             pesti_pachet.acvarii(pesti_pachet.acvarii(i).last) := :new.cod_acvariu;
             

        END IF;
    END LOOP;
END;