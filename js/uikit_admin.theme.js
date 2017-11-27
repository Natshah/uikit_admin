/**
 * @file
 * Attaches behaviors for the UIkit Admin theme.
 */

(function ($, Drupal, drupalSettings) {
  'use strict';

  /**
   * Attaches the status message closing behavior to status messages.
   *
   * Removes the #region--status_messages region from the DOM when status
   * messages are closed.
   *
   * When the hidden event on UIkit the alert component is called for each
   * status message type (status, warning, or error), the status message
   * wrapper element (.status-messages) is removed from the DOM.
   *
   * removeMessagesRegion() is then called to check if any status message
   * wrapper elements are in the DOM. If none remain, the status message
   * region is also removed from the DOM.
   *
   * @type {Drupal~behavior}
   *
   * @see status-messages.html.twig
   */
  Drupal.behaviors.uikitAdminCloseStatusMessages = {
    attach: function () {
      const $statusMessagesRegion = $('#region--status_messages');
      const $successMessages = $statusMessagesRegion.find('.uk-alert-success');
      const $warningMessages = $statusMessagesRegion.find('.uk-alert-warning');
      const $dangerMessages = $statusMessagesRegion.find('.uk-alert-danger');

      if ($successMessages.length) {
        // Status type hidden event listener.
        UIkit.util.on('.uk-alert-success', 'hidden', function (e) {
          $(e.target).parent('.status-messages').remove();
          removeMessagesRegion();
        });
      }

      if ($warningMessages.length) {
        // Warning type hidden event listener.
        UIkit.util.on('.uk-alert-warning', 'hidden', function (e) {
          $(e.target).parent('.status-messages').remove();
          removeMessagesRegion();
        });
      }

      if ($dangerMessages.length) {
        // Error type hidden event listener.
        UIkit.util.on('.uk-alert-danger', 'hidden', function (e) {
          $(e.target).parent('.status-messages').remove();
          removeMessagesRegion();
        });
      }

      // Function to remove the status messages region from the DOM.
      function removeMessagesRegion() {
        if ($statusMessagesRegion.find('.status-messages').length === 0) {
          $statusMessagesRegion.remove();
        }
      }
    }
  };

  /**
   * Attaches the table drag warning behavior to tables.
   *
   * Overrides Drupal.theme.tableDragChangedWarning function in order to
   * assign UIkit alert classes to the warning message.
   *
   * @type {Drupal~behavior}
   */
  Drupal.behaviors.uikitAdminTableDrag = {
    attach: function () {
      Drupal.theme.tableDragChangedWarning = function () {
        return `<div class="tabledrag-changed-warning messages messages--warning uk-alert uk-alert-warning" role="alert">${Drupal.theme('tableDragChangedMarker')} ${Drupal.t('You have unsaved changes.')}</div>`;
      };
    }
  };

  /**
   * Attaches the sticky navbar behavior to sticky navbars.
   *
   * @type {Drupal~behavior}
   */
  Drupal.behaviors.uikitAdminStickyNavbar = {
    attach: function () {
      const body =$('body');
      const stickyNavbar = drupalSettings.uikitAdmin.stickyNavbar;
      const header = $('#page--header');
      const navbar = $('#page--navbar');

      if (stickyNavbar) {
        header.height(navbar.outerHeight());

        navbar.css({
          'left': 0,
          'right': 0,
          'z-index': 501
        });

        // Assign initial positioning on page load.
        body.once('toolbarOrientation').each(function () {
          let fixed = body.hasClass('toolbar-fixed');
          let open = body.hasClass('toolbar-tray-open');
          let orientation = Drupal.toolbar.models.toolbarModel.get('orientation');
          setNavbarPosition(navbar, fixed, open, orientation);
        });

        // Listen for window resize event.
        $(window).on('resize', function () {
          let fixed = body.hasClass('toolbar-fixed');
          let open = body.hasClass('toolbar-tray-open');
          let orientation = Drupal.toolbar.models.toolbarModel.get('orientation');
          setNavbarPosition(navbar, fixed, open, orientation);
        });

        // Listen for toolbar orientation change event.
        $(document).on('drupalToolbarOrientationChange', function (event, orientation) {
          let fixed = body.hasClass('toolbar-fixed');
          let open = body.hasClass('toolbar-tray-open');
          setNavbarPosition(navbar, fixed, open, orientation);
        });

        // Listen for toolbar tab change event.
        $(document).on('drupalToolbarTabChange', function () {
          let fixed = body.hasClass('toolbar-fixed');
          let open = body.hasClass('toolbar-tray-open');
          let orientation = Drupal.toolbar.models.toolbarModel.get('orientation');
          setNavbarPosition(navbar, fixed, open, orientation);
        });
      }
    }
  };

  // Function to set the navbar positioning values in CSS.
  function setNavbarPosition(navbar, fixed, open, orientation) {
    const toolbarTray = $('.toolbar-tray');
    let toolbarTrayWidth = toolbarTray.outerWidth(false);

    if (orientation === 'horizontal') {
      navbar.css({
        'position': 'fixed',
        'left': 0,
      })
    }
    else {
      if (open && fixed) {
        navbar.css({
          'position': 'fixed',
          'left': toolbarTrayWidth,
        })
      }
      else if (!open && fixed) {
        navbar.css({
          'position': 'fixed',
          'left': 0,
        });
      }
      else {
        navbar.css({
          'position': 'static',
          'left': 0,
        })
      }
    }
  }
})(jQuery, Drupal, drupalSettings);
