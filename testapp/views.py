from testapp import app
from flask import render_template, request, redirect, url_for
from testapp.models.recipes import recipe
from testapp import db

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
        reci = recipe(
            name="カルボナーラ",
            times="30分",
            diff="2"
        )
        db.session.add(reci)
        db.session.commit()
        return redirect(url_for("index"))