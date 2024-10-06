from testapp import app
from flask import render_template, request, redirect, url_for
from testapp.models.recipes import recipe
from testapp import db
import pexpect
"""import requests
import os
class Image_DL():
    def save_and_rename(self, url, name=None):
        res = requests.get(url)
        if res.status_code != 200:
            return "No Image"
        path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))+"/media/image/"
        if name==None:
            path += url.split("/")[-1]
        else:
            path += name
        with open(path, 'wb') as file:
            file.write(res.content)
        return path"""

@app.route('/')
def index():
    return render_template('testapp/index.html')
"""@app.route('/recipes')
def other1():
    return render_template('testapp/index1.html')"""
@app.route('/faq')
def other2():
    return render_template('testapp/faq.html')
@app.route('/contacts')
def other3():
    return render_template('testapp/contacts.html')
@app.route('/add_recipes', methods=['GET', 'POST'])
def add_recipes():
    if request.method == 'GET':
        return render_template('testapp/add_recipes.html')
    if request.method == 'POST':
        form_recipe = request.form.get('recipe')  # str
        form_times = request.form.get('times')
        form_diff = request.form.get('diff')
        form_mat = request.form.get('mat')
        form_howto = request.form.get('howto')

        reci = recipe(
            name=form_recipe,
            times=form_times,
            diff=form_diff,
            material=form_mat,
            howto=form_howto,
            #images=""
        )
        db.session.add(reci)
        db.session.commit()
        p = pexpect.spawn('./out')
        p.sendline(form_recipe)
        p.sendline(form_mat)
        p.sendline("@end")
        p.sendline(form_howto)
        p.sendline("@end")
        p.expect("\n", timeout=None)
        p.close()
        return redirect(url_for('add_recipes'))
@app.route('/recipes')
def employee_list():
    reci = recipe.query.all()
    return render_template('testapp/recipes.html', recipes=reci)
@app.route('/recipes/<int:id>')
def employee_detail(id):
    reci = recipe.query.get(id)
    return render_template("testapp/"+reci.name+".html", recipe=reci)
@app.route('/recipes/<int:id>/delete', methods=['POST'])  
def recipe_delete(id):  
    employee = recipe.query.get(id)   
    db.session.delete(employee)  
    db.session.commit()  
    return redirect(url_for('add_recipes'))