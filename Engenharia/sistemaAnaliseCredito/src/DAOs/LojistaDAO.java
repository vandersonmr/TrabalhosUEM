/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package DAOs;

import gerenciadorCredito.Model.Lojista;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.criterion.MatchMode;
import org.hibernate.criterion.Restrictions;

/**
 *
 * @author vanderson
 */
public class LojistaDAO {

    Session s;

    public LojistaDAO() {
        s = HibernateUtil.getSessionFactory().openSession();
    }

    public void insert(Lojista lojista) {
        Transaction tx = s.beginTransaction();
        s.save(lojista);
        tx.commit();
    }
    
    public void update(Lojista lojista){
        Lojista lojistaID = getLojista(lojista);
        lojistaID.setCep(lojista.getCep());
        lojistaID.setCidade(lojista.getCidade());
        lojistaID.setCnpj(lojista.getCnpj());
        lojistaID.setEmail(lojista.getEmail());
        lojistaID.setEstado(lojista.getEstado());
        lojistaID.setNome(lojista.getNome());
        lojistaID.setPass(lojista.getPass());
        lojistaID.setRamo(lojista.getRamo());
        Transaction t = s.beginTransaction();  
        s.merge(lojistaID);  
        t.commit();
    }
    
    public void updateAdmin(Lojista lojista){
        Lojista lojistaID = getLojista(lojista);
        lojistaID.setAdmin(lojista.getAdmin());
        Transaction t = s.beginTransaction();  
        s.merge(lojistaID);  
        t.commit();
    }

    public Lojista getLojista(Lojista lojista) {
        Criteria crit;
        crit = s.createCriteria(Lojista.class).add(Restrictions.ilike("email", lojista.getEmail()));
        return (Lojista) crit.uniqueResult();
    }

    public void close() {
        s.close();
    }
}
