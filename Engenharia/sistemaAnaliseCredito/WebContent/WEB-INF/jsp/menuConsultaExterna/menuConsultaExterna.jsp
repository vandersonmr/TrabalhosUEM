<%-- 
    Document   : menuConsultaExterna
    Created on : 16/05/2013, 20:54:11
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js" ></script>
        <script type="text/javascript" src="http://igorescobar.github.io/jQuery-Mask-Plugin/js/jquery.mask.min.js"></script>
        <script src="./mascaras.js"></script>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <script src="/WEB-INF/mascara.js.js"></script>
        <title>Sistema de Análise de Crédito</title>
        <style>
            @import url("/WEB-INF/style.css");
        </style>
    </head>
    <body>
        <ul id="menu">
            <li>
                <a href="${pageContext.request.contextPath}/menu">Home</a>
            </li>
         <li>
                <a>Consultas</a>
                <ul>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaInterna">Consulta estatística</a>
                    </li>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaExterna">Consultar inadimplência</a>
                    </li>
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/gerarBoleto">Gerar Boleto</a>
            </li>
            <li>
                <a >Gerenciamento de Lojista</a>
                <ul>
                    <li><a href="${pageContext.request.contextPath}/menuNovoCadastro">Novo Cadastro</a></li>
                    <li><a href="${pageContext.request.contextPath}/menuBuscarCadastro">Buscar Cadastro</a></li>
                    <!--<li><a href="${pageContext.request.contextPath}/menuAlterarCadastro">Altera Cadastro</a></li>-->
                </ul>
            </li>
            <li>
                <a href="${pageContext.request.contextPath}/logout">Logout</a>
            </li>
        </ul>
        <h3 style="color: red;margin-left: auto; margin-right: auto" align="center">${msg}</h3>
        <form name="form1" id="consultaExternaForm" action="${pageContext.request.contextPath}/consultarExternamente" method="get">
            <fieldset>
                <legend><h1>Análise de risco realizada com o servidor afiliados da A.R.I Inc</h1></legend>

                <li>
                    <label> CPF* : </label>
                    <input type="text" name="consulta.cpf" pattern="\d{3}\.\d{3}\.\d{3}-\d{2}" 
                            id="cpf" required><br><br>
                    <label> Servidor: </label>
                    <select name="consulta.servidor">
                        <option value="SPC"> SPC</option>
                        <option value="SERASA"> SERASA</option>
                    </select>
                </li>
                <br><br>
                <li>
                    <input type="submit"  class="btn" value="Realizar Consulta"/><br>
                    <br>
                    <a href="./ajuda/ajudaConsultaExterna.html">click aqui para ajuda</a>
                <spam class="required_notification">Itens com * são obrigatórios.</spam>
                </li>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>
        </form>
    </body>
</html>
