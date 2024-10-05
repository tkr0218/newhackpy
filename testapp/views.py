from testapp import app
from flask import render_template, request, redirect, url_for
from testapp.models.recipes import recipe
from testapp import db
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
@app.route('/recipes')
def other1():
    return render_template('testapp/index1.html')
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
        reci = recipe(
            name=form_recipe,
            times=form_times,
            diff=form_diff,
            #images=""
        )
        db.session.add(reci)
        db.session.commit()
        return redirect(url_for("index"))