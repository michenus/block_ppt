(($) ->
	###
	$(document).ready ->
		owlCarusel = $('ul#pptx-line')
		owlCarusel.owlCarousel({
			loop: false
			margin: 10
			items: 5
			
			})
	###
	Drupal.behaviors.PptOwlCarusel =
		attach: (context, settings) ->
			$(document).ready ->
				owlCarusel = $('ul#pptx-line')
				owlCarusel.owlCarousel({
					loop: false
					margin: 10
					items: 5
					#itemElement: ''
					lazyLoad: true
					nav: true
					navText: ['','']
					})
) jQuery