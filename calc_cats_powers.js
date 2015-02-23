db.pages.mapReduce(function () {

	var domain_cats = {};

	domain_cats['www.igromania.ru'] = '101';
	domain_cats['games.mail.ru'] = '101';
	domain_cats['gbx.ru'] = '101';

	domain_cats['www.missfit.ru'] = '105';
	domain_cats['www.fitness.ru'] = '105';
	domain_cats['www.gymfitness.ru'] = '105';

	domain_cats['www.anekdot.ru'] = '108';
	domain_cats['anekdotov.net'] = '108';
	domain_cats['fishki.net'] = '108';
	domain_cats['lurkmore.to'] = '108';

	domain_cats['www.vseoremonte.ru'] = '115';
	domain_cats['homemasters.ru'] = '115';
	domain_cats['www.school-remont.tv'] = '115';
	domain_cats['pro-remont.com'] = '115';

	domain_cats['www.kinopoisk.ru'] = '117';
	domain_cats['www.ivi.ru'] = '117';
	domain_cats['www.imdb.com'] = '117';

	domain_cats['www.kid.ru'] = '120';
	domain_cats['mama.ru'] = '120';
	domain_cats['www.baby.ru'] = '120';
	domain_cats['selfmamaforum.ru'] = '120';

	domain_cats['www.edimdoma.ru'] = '124';
	domain_cats['www.povarenok.ru'] = '124';
	domain_cats['vpuzo.com'] = '124';
	domain_cats['www.russianfood.com'] = '124';

	domain_cats['www.petsshop.ru'] = '127';
	domain_cats['zooforum.ru'] = '127';
	domain_cats['www.pets-ural.ru'] = '127';
	domain_cats['izhpets.ru'] = '127';

	domain_cats['navalny.com'] = '128';
	domain_cats['www.ng.ru'] = '128';
	domain_cats['www.gazeta.ru'] = '128';
	domain_cats['www.echo.msk.ru'] = '128';

	domain_cats['news.sportbox.ru'] = '129';
	domain_cats['www.sport-express.ru'] = '129';
	domain_cats['www.sovsport.ru'] = '129';
	domain_cats['sport.mail.ru'] = '129';
	domain_cats['sport.rbc.ru'] = '129';

	domain_cats['habrahabr.ru'] = '130';
	domain_cats['www.cyberforum.ru'] = '130';
	domain_cats['www.linux.org.ru'] = '130';
	domain_cats['www.linux.ru'] = '130';

	domain_cats['realty.yandex.ru'] = '137';
	domain_cats['www.cian.ru'] = '137';
	domain_cats['realty.rbc.ru'] = '137';

	domain_cats['www.labirint.ru'] = '160';
	domain_cats['www.kniga.ru'] = '160';
	domain_cats['www.litres.ru'] = '160';

	domain_cats['madrobots.ru'] = '168';
	domain_cats['hi-tech.mail.ru'] = '168';
	domain_cats['onegadget.ru'] = '168';
	domain_cats['www.svyaznoy.ru'] = '168';

	domain_cats['www.muztorg.ru'] = '171';
	domain_cats['www.music-expert.ru'] = '171';
	domain_cats['www.musicalive.ru'] = '171';
	domain_cats['www.musicforums.ru'] = '171';

	domain_cats['auto.ru'] = '171';
	domain_cats['auto.mail.ru'] = '171';
	domain_cats['www.forum-auto.ru'] = '171';
	domain_cats['auto.ngs.ru'] = '171';
	
	try {
	
		var words = this.text.split(' ');
		var current_cat = domain_cats[ this.domain ];
	
		if (!current_cat)
			return;
	
		emit ( current_cat, words.length );
	
		var terms_hits = {};
	
	} catch (e) {
		
	}
},

function (key, values) {
	
	var power = 0;
	
	try {
	
		for (var i in values)
			power += values [i];
	
	} catch (e) {
		
	}
	
	return power;
},

{
	out : "cats_powers"
}

); 
