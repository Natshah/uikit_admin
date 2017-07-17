/**
 * @file
 * Attaches behaviors for the UIkit Admin theme.
 */

(function ($, Drupal) {
  'use strict';

  $(window).on({
    'scroll.TableHeader': tableHeaderOnScrollHandler
  });

  Drupal.behaviors.uikitAdminDropbuttons = {
    attach: function (context, settings) {
      var button_group = $(context).find('.uk-button-group').once('uk-dropdown');
      if (button_group.length) {
        $(button_group).each(function () {
          var dropdown = $(this).find('.uk-dropdown');
          dropdown.css('min-width', $(this).outerWidth(false) - 6);
        })
      }
    }
  };

  Drupal.behaviors.uikitAdminStickyHeaders = {
    attach: function (context, settings) {
      $(window).on({
        'scroll.TableHeader': tableHeaderOnScrollHandler()
      });
    }
  };

  function tableHeaderOnScrollHandler() {
    var stickyHeader = $('.sticky-header');

    if (!stickyHeader.hasClass('uk-table')) {
      stickyHeader.addClass('uk-table');
      stickyHeader.addClass('uk-table-striped');
    }
  }
})(jQuery, Drupal);
