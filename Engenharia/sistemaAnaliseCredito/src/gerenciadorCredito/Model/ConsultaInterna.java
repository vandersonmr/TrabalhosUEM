/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

import java.util.ArrayList;

/**
 *
 * @author vanderson
 */
public class ConsultaInterna {

    public ArrayList<LabelValue> consultarInternamente(ConsultaInternaDados consulta) {

        ArrayList<LabelValue> al = new ArrayList<LabelValue>();
        al.add(new LabelValue("Pagamento em dia ", (int) (Math.random() * 100)));
        al.add(new LabelValue("Atrasar Pagamento em até 30 dias ", (int) (Math.random() * 100)));
        al.add(new LabelValue("Atrasar Pagamento em até 60 dias ", (int) (Math.random() * 100)));
        al.add(new LabelValue("Atrasar Pagamento de Água, Luz, Telefone, Aluguel ", (int) (Math.random() * 100)));
        al.add(new LabelValue("Atrasar Pagamento de Financiamentos e Prestações ", (int) (Math.random() * 100)));
        return al;
    }
}
