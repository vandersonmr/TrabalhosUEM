/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import DAOs.LojistaDAO;
import gerenciadorCredito.Model.ConsultaExternaDados;
import gerenciadorCredito.Model.ConsultaInternaDados;
import gerenciadorCredito.Model.Lojista;
import gerenciadorCredito.Model.ValidadorCPF;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;


public class testeLojista {

    @Test
    public void testarCPFValido() {
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setCpf("954.111.058-46");
        ced.setId(1l);
        ced.setServidor("SERASA");
        assertTrue("Erro com CPF válido", ValidadorCPF.CPF(ced.getCpf()));
    }

    @Test
    public void testarCPFInvalido() {
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setCpf("954.111.000-46");
        ced.setId(1l);
        ced.setServidor("SERASA");
        assertFalse("Erro com CPF inválido", ValidadorCPF.CPF(ced.getCpf()));
    }

    @Test
    public void testarCPFInvalidoSimbolo() {
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setCpf("954111.058-46");
        ced.setId(1l);
        ced.setServidor("SERASA");
        assertTrue("Erro com CPF inválido símbolo", ValidadorCPF.CPF(ced.getCpf()));
    }

    @Test
    public void testarNULL() {
        ConsultaExternaDados ced = new ConsultaExternaDados();
        ced.setCpf(null);
        ced.setId(1l);
        ced.setServidor("SERASA");
        assertFalse("CPF null",ValidadorCPF.CPF(ced.getCpf()));
    }

    @Test
    public void testarBuscarLoginExistente() {
        Lojista l = new Lojista();
        l.setEmail("vandersonmr2@gmail.com");
        LojistaDAO ld = new LojistaDAO();
        Lojista nl = ld.getLojista(l);
        assertEquals(l.getEmail(), nl.getEmail());
    }

    @Test
    public void testarBuscarLoginNaoExistente() {
        Lojista l = new Lojista();
        l.setEmail("vandersonmsdfr2@gmail.com");
        LojistaDAO ld = new LojistaDAO();
        Lojista nl = ld.getLojista(l);
        assertNull(nl);
    }

    @Test
    public void testarBuscarLoginAdmin() {
        Lojista l = new Lojista();
        l.setEmail("admin");
        LojistaDAO ld = new LojistaDAO();
        Lojista nl = ld.getLojista(l);
        assertEquals(nl.getAdmin(),1);
    }
    // TODO add test methods here.
    // The methods must be annotated with annotation @Test. For example:
    //
    // @Test
    // public void hello() {}
}