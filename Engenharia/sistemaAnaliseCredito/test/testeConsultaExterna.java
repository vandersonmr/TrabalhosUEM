
import gerenciadorCredito.Model.ConsultaExterna;
import gerenciadorCredito.Model.ConsultaExternaDados;
import gerenciadorCredito.Model.ValidadorCPF;
import static org.junit.Assert.*;
import org.junit.Test;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author vandersonmr
 */
public class testeConsultaExterna {

    @Test
    public void testarConsultaExternaNull() {
        ConsultaExterna ce = new ConsultaExterna();
        assertNull(ce.colsutarExterna(null));
    }

    @Test
    public void testarConsultaExternaSERASA() {
        ConsultaExterna ce = new ConsultaExterna();
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setServidor("SERASA");
        assertNotNull(ce.colsutarExterna(ced));
        assertNotNull(ce.colsutarExterna(ced).getInformaçõesDoConcentre());
        assertNotNull(ce.colsutarExterna(ced).getInformaçõesDoRecheque());
        assertNotNull(ce.colsutarExterna(ced).getPendenciasFinanceiras());
    }

    @Test
    public void testarConsultaExternaSPC() {
        ConsultaExterna ce = new ConsultaExterna();
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setServidor("SPC");
        assertNotNull(ce.colsutarExterna(ced));
        assertNotNull(ce.colsutarExterna(ced).getInformaçõesDoConcentre());
        assertNotNull(ce.colsutarExterna(ced).getInformaçõesDoRecheque());
        assertNotNull(ce.colsutarExterna(ced).getPendenciasFinanceiras());
    }

    @Test
    public void testarConsultaExternaXAX() {
        ConsultaExterna ce = new ConsultaExterna();
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setServidor("XAX");
        assertNull(ce.colsutarExterna(null));
    }
}
