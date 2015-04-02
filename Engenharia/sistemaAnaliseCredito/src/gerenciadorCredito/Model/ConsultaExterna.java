/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gerenciadorCredito.Model;

/**
 *
 * @author vandersonmr
 */
public class ConsultaExterna {

    public ResultadoConsulta colsutarExterna(ConsultaExternaDados consulta) {
        String servidorNome = consulta.getServidor();
        ServidorExterno server = null;

        if (servidorNome == null) {
            return null;
        } else if (servidorNome.equalsIgnoreCase("serasa")) {
            server = new Serasa();
        } else if (servidorNome.equalsIgnoreCase("spc")) {
            server = new SPC();
        } else {
            return null;
        }

        return server.consultar(consulta);
    }
}
