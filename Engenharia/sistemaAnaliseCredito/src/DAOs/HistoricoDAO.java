/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DAOs;

import gerenciadorCredito.Model.Historico;
import gerenciadorCredito.Model.Lojista;
import java.util.ArrayList;
import java.util.List;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.criterion.MatchMode;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Restrictions;

/**
 *
 * @author vanderson
 */
public class HistoricoDAO {

    Session s;

    public HistoricoDAO() {
        s = HibernateUtil.getSessionFactory().openSession();
    }

    public void insert(Historico his) {
        Transaction tx = s.beginTransaction();
        s.save(his);
        tx.commit();
    }
    
    public List getLasts(){
        Criteria crit = s.createCriteria(Historico.class);
        crit.addOrder(Order.desc("id"));
        crit.setMaxResults(30);
        return crit.list();    
    }
    
    public List<String> getEstatisticas(){
        List<String> l = new ArrayList<String>();
        l.add("Quantidade de lojistas cadastrados: "+s.createSQLQuery("select count(*) from LOJISTA").uniqueResult());
        l.add("Quantidade de lojistas desabilitados: "+ s.createSQLQuery("select count(*) from LOJISTA where ADMIN=-1").uniqueResult());
        l.add("Quantidade de consultas externas realizadas: "+s.createSQLQuery("select count(*) from HISTORICO where STATUS=10").uniqueResult());
        l.add("Quantidade de consultas internas realizadas: "+ s.createSQLQuery("select count(*) from HISTORICO where STATUS=11").uniqueResult());
        l.add("Quantidade de boletos gerados: "+ s.createSQLQuery("select count(*) from HISTORICO where STATUS=12").uniqueResult());
        return l;
    }
    
    
    public void close() {
        s.close();
    }
}
