/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author vanderson
 */
public class ResultadoConsulta {
    private List<String> pendenciasFinanceiras = new ArrayList<String>();
    private List<String> informaçõesDoConcentre = new ArrayList<String>();
    private List<String> informaçõesDoRecheque = new ArrayList<String>();

    public List<String> getPendenciasFinanceiras() {
        return pendenciasFinanceiras;
    }

    public void setPendenciasFinanceiras(List<String> pendenciasFinanceiras) {
        this.pendenciasFinanceiras = pendenciasFinanceiras;
    }

    public List<String> getInformaçõesDoConcentre() {
        return informaçõesDoConcentre;
    }

    public void setInformaçõesDoConcentre(List<String> informaçõesDoConcentre) {
        this.informaçõesDoConcentre = informaçõesDoConcentre;
    }

    public List<String> getInformaçõesDoRecheque() {
        return informaçõesDoRecheque;
    }

    public void setInformaçõesDoRecheque(List<String> informaçõesDoRecheque) {
        this.informaçõesDoRecheque = informaçõesDoRecheque;
    }
    
    
}
