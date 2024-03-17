/*
 * jQuery Easing v1.3 - http://gsgd.co.uk/sandbox/jquery/easing/
 *
 * Uses the built in easing capabilities added In jQuery 1.1
 * to offer multiple easing options
 *
 * TERMS OF USE - jQuery Easing
 * 
 * Open source under the BSD License. 
 * 
 * Copyright © 2008 George McGinley Smith
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of 
 * conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * 
 * Neither the name of the author nor the names of contributors may be used to endorse 
 * or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
*/

// t: current time, b: begInnIng value, c: change In value, d: duration
jQuery.easing['jswing'] = jQuery.easing['swing'];

jQuery.extend( jQuery.easing,
{
	def: 'easeOutQuad',
	swing: function (x, t, b, c, d) {
		//alert(jQuery.easing.default);
		return jQuery.easing[jQuery.easing.def](x, t, b, c, d);
	},
	easeInQuad: function (x, t, b, c, d) {
		return c*(t/=d)*t + b;
	},
	easeOutQuad: function (x, t, b, c, d) {
		return -c *(t/=d)*(t-2) + b;
	},
	easeInOutQuad: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t + b;
		return -c/2 * ((--t)*(t-2) - 1) + b;
	},
	easeInCubic: function (x, t, b, c, d) {
		return c*(t/=d)*t*t + b;
	},
	easeOutCubic: function (x, t, b, c, d) {
		return c*((t=t/d-1)*t*t + 1) + b;
	},
	easeInOutCubic: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t*t + b;
		return c/2*((t-=2)*t*t + 2) + b;
	},
	easeInQuart: function (x, t, b, c, d) {
		return c*(t/=d)*t*t*t + b;
	},
	easeOutQuart: function (x, t, b, c, d) {
		return -c * ((t=t/d-1)*t*t*t - 1) + b;
	},
	easeInOutQuart: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
		return -c/2 * ((t-=2)*t*t*t - 2) + b;
	},
	easeInQuint: function (x, t, b, c, d) {
		return c*(t/=d)*t*t*t*t + b;
	},
	easeOutQuint: function (x, t, b, c, d) {
		return c*((t=t/d-1)*t*t*t*t + 1) + b;
	},
	easeInOutQuint: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
		return c/2*((t-=2)*t*t*t*t + 2) + b;
	},
	easeInSine: function (x, t, b, c, d) {
		return -c * Math.cos(t/d * (Math.PI/2)) + c + b;
	},
	easeOutSine: function (x, t, b, c, d) {
		return c * Math.sin(t/d * (Math.PI/2)) + b;
	},
	easeInOutSine: function (x, t, b, c, d) {
		return -c/2 * (Math.cos(Math.PI*t/d) - 1) + b;
	},
	easeInExpo: function (x, t, b, c, d) {
		return (t==0) ? b : c * Math.pow(2, 10 * (t/d - 1)) + b;
	},
	easeOutExpo: function (x, t, b, c, d) {
		return (t==d) ? b+c : c * (-Math.pow(2, -10 * t/d) + 1) + b;
	},
	easeInOutExpo: function (x, t, b, c, d) {
		if (t==0) return b;
		if (t==d) return b+c;
		if ((t/=d/2) < 1) return c/2 * Math.pow(2, 10 * (t - 1)) + b;
		return c/2 * (-Math.pow(2, -10 * --t) + 2) + b;
	},
	easeInCirc: function (x, t, b, c, d) {
		return -c * (Math.sqrt(1 - (t/=d)*t) - 1) + b;
	},
	easeOutCirc: function (x, t, b, c, d) {
		return c * Math.sqrt(1 - (t=t/d-1)*t) + b;
	},
	easeInOutCirc: function (x, t, b, c, d) {
		if ((t/=d/2) < 1) return -c/2 * (Math.sqrt(1 - t*t) - 1) + b;
		return c/2 * (Math.sqrt(1 - (t-=2)*t) + 1) + b;
	},
	easeInElastic: function (x, t, b, c, d) {
		var s=1.70158;var p=0;var a=c;
		if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
		if (a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		return -(a*Math.pow(2,10*(t-=1)) * Math.sin( (t*d-s)*(2*Math.PI)/p )) + b;
	},
	easeOutElastic: function (x, t, b, c, d) {
		var s=1.70158;var p=0;var a=c;
		if (t==0) return b;  if ((t/=d)==1) return b+c;  if (!p) p=d*.3;
		if (a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		return a*Math.pow(2,-10*t) * Math.sin( (t*d-s)*(2*Math.PI)/p ) + c + b;
	},
	easeInOutElastic: function (x, t, b, c, d) {
		var s=1.70158;var p=0;var a=c;
		if (t==0) return b;  if ((t/=d/2)==2) return b+c;  if (!p) p=d*(.3*1.5);
		if (a < Math.abs(c)) { a=c; var s=p/4; }
		else var s = p/(2*Math.PI) * Math.asin (c/a);
		if (t < 1) return -.5*(a*Math.pow(2,10*(t-=1)) * Math.sin( (t*d-s)*(2*Math.PI)/p )) + b;
		return a*Math.pow(2,-10*(t-=1)) * Math.sin( (t*d-s)*(2*Math.PI)/p )*.5 + c + b;
	},
	easeInBack: function (x, t, b, c, d, s) {
		if (s == undefined) s = 1.70158;
		return c*(t/=d)*t*((s+1)*t - s) + b;
	},
	easeOutBack: function (x, t, b, c, d, s) {
		if (s == undefined) s = 1.70158;
		return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
	},
	easeInOutBack: function (x, t, b, c, d, s) {
		if (s == undefined) s = 1.70158; 
		if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525))+1)*t - s)) + b;
		return c/2*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2) + b;
	},
	easeInBounce: function (x, t, b, c, d) {
		return c - jQuery.easing.easeOutBounce (x, d-t, 0, c, d) + b;
	},
	easeOutBounce: function (x, t, b, c, d) {
		if ((t/=d) < (1/2.75)) {
			return c*(7.5625*t*t) + b;
		} else if (t < (2/2.75)) {
			return c*(7.5625*(t-=(1.5/2.75))*t + .75) + b;
		} else if (t < (2.5/2.75)) {
			return c*(7.5625*(t-=(2.25/2.75))*t + .9375) + b;
		} else {
			return c*(7.5625*(t-=(2.625/2.75))*t + .984375) + b;
		}
	},
	easeInOutBounce: function (x, t, b, c, d) {
		if (t < d/2) return jQuery.easing.easeInBounce (x, t*2, 0, c, d) * .5 + b;
		return jQuery.easing.easeOutBounce (x, t*2-d, 0, c, d) * .5 + c*.5 + b;
	}
});

/*
 *
 * TERMS OF USE - EASING EQUATIONS
 * 
 * Open source under the BSD License. 
 * 
 * Copyright © 2001 Robert Penner
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of 
 * conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * 
 * Neither the name of the author nor the names of contributors may be used to endorse 
 * or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 */;
/*
# ------------------------------------------------------------------------
# JD Base Theme
# ------------------------------------------------------------------------
# Copyright (C) 2004-2010 JoomlArt.com. All Rights Reserved.
# @license GNU/GPLv3 http://www.gnu.org/licenses/gpl-3.0.html
# Author: JoomlArt.com
# Websites: http://www.joomlart.com - http://www.joomlancers.com.
# ------------------------------------------------------------------------
 */
(function(jQuery) {
	jQuery.fn.JDMegaMenu = function(vars) {
		vars = vars != undefined ? vars : {};
		var durationIn = vars.durationIn == undefined ? 300 : vars.durationIn;
		var durationOut = vars.durationOut == undefined ? 400
				: vars.durationOut;
		var effectIn = vars.effectIn == undefined ? 'jswing' : vars.effectIn;
		var effectOut = vars.effectOut == undefined ? 'jswing' : vars.effectOut;
		var delay = vars.delay == undefined ? 1000 : vars.delay;
		var direction = vars.direction == undefined ? 0 : vars.direction;
		var wdWidth = jQuery(window).width();
		/* Fix getting browser window width for IE */
		var IE = jQuery.browser.msie;
		if (IE) {
			if (wdWidth < jQuery(document).width())
				wdWidth = jQuery(document).width();
		}
		var timeout = null;
		var currentId = null;
		var rtl = false;
		var hideside = direction ? 'right' : 'left';
		var marginside1 = direction ? 'margin-right' : 'margin-left';

		/* Set menu in the default style */
		jQuery('.childcontent').each(
				function() {
					var height = jQuery(this).height();
					jQuery('.childcontent-inner-wrap', this).css('top',
							'-' + height + 'px');
				});

		var overflow = function(id, hidden) {
			if (hidden) {
				jQuery('.childcontent-' + id).css('overflow', 'hidden');
			} else
				jQuery('.childcontent-' + id).css('overflow', '');
		}
		/* Check and Set rtl mode */
		var checkRTL = function(sub) {
			var docWidth = jQuery(document).width();
			if (docWidth > wdWidth) {
				rtl = true;
				if (sub)
					wdWidth = docWidth;
			} else
				rtl = false;
		}
		// console.log('donglt');
		/* Show a level 0 menu */
		var slidedown = function() {
			var childcontent = jQuery('.childcontent-' + currentId);
			/* Reset rtl mode */
			if (childcontent.hasClass('rtl')) {
				rtl = true;
			} else {
				if (childcontent.hasClass('ltr'))
					rtl = false;
				else {
					childcontent.css('right', 'auto');
					checkRTL(0);
				}
			}

			if (rtl) {
				var width = childcontent.width();
				var m_width = jQuery('.main').width();
				var left = (m_width - width) / 2;
				childcontent.css(hideside, left + 'px');
				childcontent.addClass('rtl');
			} else {
				childcontent.addClass('ltr');
				childcontent.css(hideside, 'auto');
			}
			if (direction) { // fix for Chrome, Opera
				childcontent.css('visibility', 'visible');
				childcontent.css('position', 'absolute');
				if (IE) {// Fix IE
					childcontent.css(hideside, '0');
					childcontent.parent().css('position', 'relative');
				}
			}
			jQuery('.childcontent-inner-wrap-' + currentId).stop(true, false)
					.animate( {
						'top' : 0
					}, durationIn, effectIn, function() {
						overflow(currentId, 0);
					});
		}
		/* Hide a level 0 menu */
		var slideup = function() {
			/* Backup currentId */
			var id = currentId;
			overflow(id, 1);
			var height = jQuery('.childcontent-' + currentId).height();
			jQuery('.childcontent-inner-wrap-' + currentId)
					.stop(true, false)
					.animate(
							{
								'top' : '-' + height + 'px'
							},
							durationOut,
							effectOut,
							function() {
								jQuery('.childcontent-' + id).css(hideside, '');
								if (direction) {// fix for Chrome, Opera
									jQuery('.childcontent-' + id).css(
											'visibility', 'hidden');
									jQuery('.childcontent-' + id).css(
											'position', 'fixed');
								}
							});
		}

		/* Show a sub menu */
		var showChild = function(id) {
			var childcontent = jQuery('.childcontent-' + id);
			var childcontentinnerwrap = jQuery('.childcontent-inner-wrap-' + id);
			var t = jQuery('#' + id);
			var width = childcontentinnerwrap.width();
			var cur_rtl = rtl;
			var pr_width = jQuery('#' + id).parent().parent().width();

			var l_width = width;
			/*
			 * Check available expand direction of element is right to left or
			 * reverse
			 */
			if (t.hasClass('rtl')) {
				childcontent.css(marginside1, '-' + l_width + 'px');
				childcontent.css('top', '');
				childcontent.css(hideside, 'auto');
			}
			if (t.hasClass('ltr')) {
				childcontent.css(hideside, 'auto');
			}
			if (!t.hasClass('rtl') && !t.hasClass('ltr')) {
				/* Expand in hidden to get temporary width of document */

				childcontent.css(hideside, 'auto');
				/*
				 * Compare the width of window and document to decide the
				 * direction
				 */
				checkRTL(1);
				/* Setup position */
				if (rtl) {
					childcontent.css(marginside1, '-' + l_width + 'px');
					childcontent.css('top', '');
					childcontentinnerwrap.css(marginside1, width);
					childcontent.css(hideside, 'auto');
					/* Add a class for caching */
					t.addClass('rtl');
				} else {
					childcontent.css(hideside, 'auto');
					/* Add a class for caching */
					t.addClass('ltr');
				}
			}
			childcontentinnerwrap.css('top', '');
			/* Add a class for menu status */
			t.addClass('showing');
			/* Begin animating */
			if (direction) {
				childcontent.css('visibility', 'visible');
				childcontent.css('position', 'absolute');
				childcontentinnerwrap.stop(true, false).animate( {
					'marginRight' : '0px'
				}, durationIn, effectIn, function() {
					overflow(id, 0);
				});
			} else {
				childcontentinnerwrap.stop(true, false).animate( {
					'marginLeft' : '0px'
				}, durationIn, effectIn, function() {
					overflow(id, 0);
				});
			}
		}
		/* Hide a sub menu */
		var hideChild = function(id) {
			var childcontent = jQuery('.childcontent-' + id);
			var childcontentinnerwrap = jQuery('.childcontent-inner-wrap-' + id);
			var t = jQuery('#' + id);
			var height = childcontent.height();
			var width = childcontentinnerwrap.css('width');
			overflow(id, 1);
			/* Remove status */
			t.removeClass('showing');
			if (t.hasClass('rtl')) {
				/* Stop current animation and Begin hiding animation */
				if (direction) {
					childcontentinnerwrap.stop(true, false).animate( {
						'marginRight' : width
					}, durationOut, effectOut, function() {
						childcontent.css(hideside, '');
						childcontentinnerwrap.css('top', '-' + height + 'px');
						childcontent.css('visibility', 'hidden');
						childcontent.css('position', 'fixed');
					});
				} else {
					childcontentinnerwrap.stop(true, false).animate( {
						'marginLeft' : width
					}, durationOut, effectOut, function() {
						childcontent.css(hideside, '');
						childcontentinnerwrap.css('top', '-' + height + 'px');
					});
				}
			} else {
				/* Stop current animation and Begin hiding animation */
				if (direction) {
					childcontentinnerwrap.stop(true, false).animate( {
						'marginRight' : '-' + width
					}, durationOut, effectOut, function() {
						childcontent.css(hideside, '');
						childcontentinnerwrap.css('top', '-' + height + 'px');
						childcontent.css('visibility', 'hidden');
						childcontent.css('position', 'fixed');
					});
				} else {
					childcontentinnerwrap.stop(true, false).animate( {
						'marginLeft' : '-' + width
					}, durationOut, effectOut, function() {
						childcontent.css(hideside, '');
						childcontentinnerwrap.css('top', '-' + height + 'px');
					});
				}
			}

		}
		/* Collect menu items */
		jQuery('.ja-megamenu  li').each(
				function() {
					var id = jQuery(this).attr('id');
					/* Set sub-menu style in default LTR */
					if (!jQuery(this).parent().hasClass('level0')) {
						var width = jQuery('.childcontent-inner-wrap-' + id)
								.css('width');
						jQuery('.childcontent-inner-wrap-' + id).css(
								marginside1, '-' + width);
					}
					/* Bind the mouseover event to each menu item */
					jQuery(this).bind(
							'mouseenter',
							function(event) {
								if (!jQuery(this).hasClass('over')
										&& !jQuery(this).hasClass('group')) {
									jQuery(this).addClass('over');
									jQuery('a', this).eq(0).addClass('over');
								}
								clearTimeout(timeout);
								timeout = null;
								/* Mouseover a level 0 menu item */
								if (jQuery(this).parent().hasClass('level0')) {
									if (currentId && id != currentId) {
										slideup();
									}
									if (jQuery(this).hasClass('haschild')) {
										currentId = id;
										slidedown();
									}
								}
								/* Mouseover a sub-menu item */
								else {
									if (jQuery(this).hasClass('haschild')
											&& !jQuery(this)
													.hasClass('showing')) {
										showChild(id);
									}
								}
							});
					/* Bind the mouseleave event to sub-menu items */
					jQuery(this).bind('mouseleave', function() {
						jQuery(this).removeClass('over');
						jQuery('a', this).eq(0).removeClass('over');
						if (!jQuery(this).parent().hasClass('level0')) {
							if (jQuery(this).hasClass('haschild')) {
								hideChild(id);
							}
						}
					});
				});
		/* Bind the mouseout event to menu */
		jQuery('.ja-megamenu').bind('mouseleave', function() {
			if (currentId) {
				/* delay to hide menu item */
				timeout = setTimeout(slideup, delay);
			}
		});
		/* Fix cursor for IE6 & IE7 */
		jQuery('.ja-megamenu span').css('cursor', 'pointer');
	}

})(jQuery);;
/**
 * Cookie plugin
 *
 * Copyright (c) 2006 Klaus Hartl (stilbuero.de)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 */

/**
 * Create a cookie with the given name and value and other optional parameters.
 *
 * @example $.cookie('the_cookie', 'the_value');
 * @desc Set the value of a cookie.
 * @example $.cookie('the_cookie', 'the_value', { expires: 7, path: '/', domain: 'jquery.com', secure: true });
 * @desc Create a cookie with all available options.
 * @example $.cookie('the_cookie', 'the_value');
 * @desc Create a session cookie.
 * @example $.cookie('the_cookie', null);
 * @desc Delete a cookie by passing null as value. Keep in mind that you have to use the same path and domain
 *       used when the cookie was set.
 *
 * @param String name The name of the cookie.
 * @param String value The value of the cookie.
 * @param Object options An object literal containing key/value pairs to provide optional cookie attributes.
 * @option Number|Date expires Either an integer specifying the expiration date from now on in days or a Date object.
 *                             If a negative value is specified (e.g. a date in the past), the cookie will be deleted.
 *                             If set to null or omitted, the cookie will be a session cookie and will not be retained
 *                             when the the browser exits.
 * @option String path The value of the path atribute of the cookie (default: path of page that created the cookie).
 * @option String domain The value of the domain attribute of the cookie (default: domain of page that created the cookie).
 * @option Boolean secure If true, the secure attribute of the cookie will be set and the cookie transmission will
 *                        require a secure protocol (like HTTPS).
 * @type undefined
 *
 * @name $.cookie
 * @cat Plugins/Cookie
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

/**
 * Get the value of a cookie with the given name.
 *
 * @example $.cookie('the_cookie');
 * @desc Get the value of a cookie.
 *
 * @param String name The name of the cookie.
 * @return The value of the cookie.
 * @type String
 *
 * @name $.cookie
 * @cat Plugins/Cookie
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */
jQuery.cookie = function(name, value, options) {
    if (typeof value != 'undefined') { // name and value given, set cookie
        options = options || {};
        if (value === null) {
            value = '';
            options.expires = -1;
        }
        var expires = '';
        if (options.expires && (typeof options.expires == 'number' || options.expires.toUTCString)) {
            var date;
            if (typeof options.expires == 'number') {
                date = new Date();
                date.setTime(date.getTime() + (options.expires * 24 * 60 * 60 * 1000));
            } else {
                date = options.expires;
            }
            expires = '; expires=' + date.toUTCString(); // use expires attribute, max-age is not supported by IE
        }
        // CAUTION: Needed to parenthesize options.path and options.domain
        // in the following expressions, otherwise they evaluate to undefined
        // in the packed version for some reason...
        var path = options.path ? '; path=' + (options.path) : '';
        var domain = options.domain ? '; domain=' + (options.domain) : '';
        var secure = options.secure ? '; secure' : '';
        document.cookie = [name, '=', encodeURIComponent(value), expires, path, domain, secure].join('');
    } else { // only name given, get cookie
        var cookieValue = null;
        if (document.cookie && document.cookie != '') {
            var cookies = document.cookie.split(';');
            for (var i = 0; i < cookies.length; i++) {
                var cookie = jQuery.trim(cookies[i]);
                // Does this cookie string begin with the name we want?
                if (cookie.substring(0, name.length + 1) == (name + '=')) {
                    cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                    break;
                }
            }
        }
        return cookieValue;
    }
};;
