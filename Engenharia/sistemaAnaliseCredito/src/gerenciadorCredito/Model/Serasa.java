/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

import java.util.List;

/**
 *
 * @author vanderson
 */
public class Serasa implements ServidorExterno{

    public ResultadoConsulta consultar(ConsultaExternaDados consulta) {
        ResultadoConsulta res = new ResultadoConsulta();
        res.getInformaçõesDoConcentre().add("OK");
        res.getInformaçõesDoRecheque().add("OK");
        List<String> aux = res.getPendenciasFinanceiras();
        aux.add("OK");
        res.setPendenciasFinanceiras(aux);
        return res;
    }
    
}
