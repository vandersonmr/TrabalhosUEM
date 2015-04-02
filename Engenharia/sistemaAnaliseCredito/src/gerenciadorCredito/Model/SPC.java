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
public class SPC implements ServidorExterno{
    private boolean getChance(){
        double x = Math.random();
        return x<0.5;
    }
    public ResultadoConsulta consultar(ConsultaExternaDados consulta) {
                ResultadoConsulta res = new ResultadoConsulta();
        if(getChance()) res.getInformaçõesDoConcentre().add("Cheque xxx atrasado");
        if(getChance()) res.getInformaçõesDoConcentre().add("Dívida de xxx reais");
        if(getChance()) res.getInformaçõesDoConcentre().add("Ação judicial xxx código xxx");
        if(getChance()) res.getInformaçõesDoConcentre().add("Nome em protesto pela empresa xxx");
        if(res.getInformaçõesDoConcentre().isEmpty()){
            res.getInformaçõesDoConcentre().add("OK");
        }
        if(getChance()) res.getInformaçõesDoRecheque().add("Cheque voltou valor xxx");
        if(getChance()) res.getInformaçõesDoRecheque().add("Cheque sustado valor xxx");
       
        if(res.getInformaçõesDoRecheque().isEmpty()){
            res.getInformaçõesDoRecheque().add("OK");
        }
        
        if(getChance()) res.getPendenciasFinanceiras().add("Dívida de xxx reais");
        if(getChance()) res.getPendenciasFinanceiras().add("Dívida de yyy reais");
        if(getChance()) res.getPendenciasFinanceiras().add("Dívida de uuu reais");
        if(res.getInformaçõesDoRecheque().isEmpty()){
            res.getPendenciasFinanceiras().add("OK");
        }
        return res;
    }
    
}
