<%-- 
    Document   : menuConsultaInterna
    Created on : 16/05/2013, 19:36:51
    Author     : vanderson
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js" ></script>
        <script type="text/javascript" src="http://igorescobar.github.io/jQuery-Mask-Plugin/js/jquery.mask.min.js"></script>
        <script src="./mascaras.js"></script>
        <script src="/WEB-INF/sha256.js"></script>
        <script src="/WEB-INF/mascara.js.js"></script>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
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
                <a >Consultas</a>
                <ul>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaInterna">Servidor Local</a>
                    </li>
                    <li>
                        <a href="${pageContext.request.contextPath}/menuConsultaExterna">Servidor Externo</a>
                    </li>
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/gerarBoleto">Gerar Boleto</a>
            <li>
            <li>
                <a >Gerenciamento de Lojista</a>
                <ul>
                    <li><a href="${pageContext.request.contextPath}/menuNovoCadastro">Novo Cadastro</a></li>
                    <li><a href="${pageContext.request.contextPath}/menuBuscarCadastro">Buscar Cadastro</a></li>
                  <!-- <li><a href="${pageContext.request.contextPath}/menuAlterarCadastro">Altera Cadastro</a></li>-->
                </ul>
            <li>
            <li>
                <a href="${pageContext.request.contextPath}/logout">Logout</a>
            <li>
        </ul>
        <form action="${pageContext.request.contextPath}/alterarCadastro" method="post">

            <fieldset>
                <legend><h1>Cadastro de Lojista A.R.I Inc</h1></legend>

                <li>
                    <label> CNPJ* (00000-000): </label><input name="lojista.cnpj" pattern="\d{5}-\d{3}" value="${loj.cnpj}" required/><br><br>
                </li>

                <!-- <li>
                    <label> Código Login* (000.000.000): </label><input name="lojista.login" pattern="\d{3}.\d{3}.\d{3}" required/><br><br>
                </li>-->

                <li>
                    <label> Nome: </label><input name="lojista.nome" value="${loj.nome}"/> <br><br>
                </li>


                <li>
                    <label> Ramo: </label><input name="lojista.ramo" value="${loj.ramo}"/> <br><br>
                </li>

                <li>
                    <label> Estado: </label> <select name="lojista.estado"> 
                        <option value="estado">Selecione o Estado</option> 
                        <option value="ac">Acre</option> 
                        <option value="al">Alagoas</option> 
                        <option value="am">Amazonas</option> 
                        <option value="ap">Amapá</option> 
                        <option value="ba">Bahia</option> 
                        <option value="ce">Ceará</option> 
                        <option value="df">Distrito Federal</option> 
                        <option value="es">Espírito Santo</option> 
                        <option value="go">Goiás</option> 
                        <option value="ma">Maranhão</option> 
                        <option value="mt">Mato Grosso</option> 
                        <option value="ms">Mato Grosso do Sul</option> 
                        <option value="mg">Minas Gerais</option> 
                        <option value="pa">Pará</option> 
                        <option value="pb">Paraíba</option> 
                        <option value="pr">Paraná</option> 
                        <option value="pe">Pernambuco</option> 
                        <option value="pi">Piauí</option> 
                        <option value="rj">Rio de Janeiro</option> 
                        <option value="rn">Rio Grande do Norte</option> 
                        <option value="ro">Rondônia</option> 
                        <option value="rs">Rio Grande do Sul</option> 
                        <option value="rr">Roraima</option> 
                        <option value="sc">Santa Catarina</option> 
                        <option value="se">Sergipe</option> 
                        <option value="sp">São Paulo</option> 
                        <option value="to">Tocantins</option> 
                    </select>
                </li>
                <br>

                <li>
                    <label> CEP (00000-000): </label><input name="lojista.cep" value="${loj.cep}" 
                                                    id="cep" /> 
                </li>
                <br>

                <li>
                    <label> Cidade: </label><input name="lojista.cidade" value="${loj.cidade}"/> 
                </li>
                <br>

                <li>
                    <label> Email*: </label><input name="lojista.email" type="email" value="${loj.email}" required/> 
                </li>
                <br>

                <li>
                    <label> Senha*: </label> <input type="password" id ="pass" name="lojista.pass" required/>
                </li>
                <br>

                <br>
                <li>
                    <input type="submit"  class="btn" value="Salvar modificações" onClick="document.getElementById('pass').value
                                       =new jsSHA(document.getElementById('pass')
                                       .value, 'TEXT').getHash('SHA-256', 'HEX');
                                       document.forms['loginForm'].submit();"><br>
                                    <li>

                <center><form action="${pageContext.request.contextPath}/menu">
                        <input type="submit" onClick="window.history.back()" class="btn" value="Voltar"><br>
                    </form></center>
                <spam class="required_notification">Itens com * são obrigatórios.</spam>
                </li>
                <br><br>
                Sistema de Análise de Crédito. 2013. Criado pela equipe <a href="sobre.html">Lobos</a>.
            </fieldset>
        </form>
    </body>
</html>
